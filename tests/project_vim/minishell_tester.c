/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:34:18 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/26 11:06:03 by lbiasuz          ###   ########.fr       */
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
		printf("Usage: ./test_minishell.a path_to_test_file\n");
		exit(0);
	}
	g_info.file_path = argv[1];
	(void)envp;
}

static void	child_func(void)
{
	printf("Child PID:%i", g_info.pid);
	dup2(g_info.pipe[0], STDIN_FILENO);
	dup2(g_info.pipe2[1], STDOUT_FILENO);
	close(g_info.pipe[1]);
	close(g_info.pipe2[0]);
	execve("bbonaldi/minishell", NULL, NULL);
	perror("child_func:execve");
	exit (1);
}

static void	parent_func(void)
{
	int		read_bytes;
	char	*buff;

	read_bytes = 1;
	printf("His PID is:%i\n", g_info.pid);
	apply_test(&g_info.pipe[1]);
	close_pipe(g_info.pipe);
	close(g_info.pipe2[1]);
	wait(0);
	wait(0);
	wait(0);
	wait(0);
	wait(0);
	buff = get_next_line(g_info.pipe2[0]);
	while (buff)
	{
		printf("%s", buff);
		buff = get_next_line(g_info.pipe2[0]);
	}
	close_pipe(g_info.pipe2);
}

static void	close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}
