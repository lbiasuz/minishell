/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:34:18 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/18 20:34:19 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell_tester.h"

t_info	g_info;

static void	init(int argc, char **argv, char **envp);
static void	child_func(void);
static void	parent_func(void);
static void	close_pipe(int *pipe);

int	main(int argc, char **argv, char **envp)
{
	init(argc, argv, envp);
	pipe(g_info.pipe);
	pipe(g_info.pipe2);
	g_info.pid = fork();
	if (g_info.pid == 0)
		child_func();
	else
		parent_func();
	printf("DONE\n");
	return (0);
}

static void	init(int argc, char **argv, char **envp)
{
	if (argc != 2)
	{
		printf("Usage: ./a.out [path_to_test_file]");
		exit(0);
	}
	g_info.file_path = argv[1];
	(void)envp;
}

static void	child_func(void)
{
	dup2(g_info.pipe[0], STDIN_FILENO);
	dup2(g_info.pipe2[1], STDOUT_FILENO);
	close(g_info.pipe[1]);
	close(g_info.pipe2[0]);
	execve("../../minishell", NULL, NULL);
}

static void	parent_func(void)
{
	int	read_bytes;
	char	buff[5];

	read_bytes = 1;
	printf("His PID is:%i\n", g_info.pid);
	// apply_test(&g_info.pipe[1]);
	write(g_info.pipe[1], "exit\n", 5);
	wait(NULL);
	close_pipe(g_info.pipe);
	close(g_info.pipe2[1]);
	while (read_bytes > 0)
	{
		read_bytes = read(g_info.pipe2[0], buff, 4);
		buff[read_bytes] = 0;
		printf("%s", buff);
	}
	close_pipe(g_info.pipe2);
}

static void	close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

