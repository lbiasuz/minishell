/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:55:07 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/03 02:12:55 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

static void	set_heredoc_signal_handlers(void);

int	file_to_stdin(char *filepath, int current_fd)
{
	int			fd;
	static int	old_file;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		g_ms.exit_code = 1;
		perror(filepath);
		return (current_fd);
	}
	if (old_file)
		close(old_file);
	old_file = fd;
	return (fd);
}

int	stdout_to_file(char *filepath, int current_fd)
{
	int			fd;
	static int	old_file;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if (fd == -1)
	{
		g_ms.exit_code = 1;
		perror(filepath);
		return (current_fd);
	}
	if (old_file)
		close(old_file);
	old_file = fd;
	return (fd);
}

int	heredoc_to_stdin(char *stop_str, int current_fd)
{
	char	*buff;
	int		stop_str_len;
	int		fd[2];
	static int	old_heredoc;

	if (pipe(fd) == -1)
	{
		g_ms.exit_code = 1;
		return (current_fd);
	}
	stop_str_len = ft_strlen(stop_str);
	set_heredoc_signal_handlers();
	buff = readline("> ");
	while (buff && ft_strncmp(stop_str, buff, stop_str_len))
	{
		ft_putendl_fd(buff, fd[1]);
		free(buff);
		rl_on_new_line();
		buff = readline("> ");
	}
	set_heredoc_signal_handlers();
	if (buff)
		free(buff);
	if (old_heredoc)
		close(old_heredoc);
	old_heredoc = fd[0];
	close(fd[1]);
	return (fd[0]);
}

int	append_stdout_to_file(char *filepath, int current_fd)
{
	int			fd;
	static int	old_file;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
	if (fd == -1)
	{
		g_ms.exit_code = 1;
		perror(filepath);
		return (current_fd);
	}
	if (old_file)
		close(old_file);
	old_file = fd;
	return (fd);
}

static void	func_heredoc_handler(int signo)
{
	(void)signo;
	g_ms.exit_code = 130;
	write(2, "\n", 1);
	exit(130);
}

static void	set_heredoc_signal_handlers(void)
{
	t_sigaction			act;
	static t_sigaction	old_act;
	static int			restore_flag;

	if (restore_flag++)
	{
		sigaction(SIGINT, &old_act, NULL);
		restore_flag--;
		return ;
	}
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = &func_heredoc_handler;
	sigaction(SIGINT, &act, &old_act);
}
