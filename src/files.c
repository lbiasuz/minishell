/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:55:07 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/04 16:25:53 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

static char	*heredoc_loop(char *buff, int fd)
{
	ft_putendl_fd(buff, fd);
	free(buff);
	rl_on_new_line();
	return (readline("> "));
}

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
	char		*buff;
	int			stop_str_sz;
	int			fd[2];
	static int	old_heredoc;

	if (pipe(fd) == -1)
	{
		g_ms.exit_code = 1;
		return (current_fd);
	}
	stop_str_sz = sizeof(stop_str);
	set_heredoc_signal_handlers();
	buff = readline("> ");
	while (buff && ft_strncmp(stop_str, buff, stop_str_sz))
		buff = heredoc_loop(buff, fd[1]);
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
