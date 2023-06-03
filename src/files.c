/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:55:07 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/02 23:01:05 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

int	file_to_stdin(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		g_ms.exit_code = 1;
		perror(filepath);
	}
	else
		dup2(fd, current_fd);
	return (fd);
}

int	stdout_to_file(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if (fd == -1)
	{
		g_ms.exit_code = 1;
		perror(filepath);
	}
	else
		dup2(fd, current_fd);
	return (fd);
}

int	heredoc_to_stdin(char *stop_str, int current_fd)
{
	char	*buff;
	int		stop_str_len;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		g_ms.exit_code = 1;
		return (current_fd);
	}
	stop_str_len = ft_strlen(stop_str);
	buff = readline("> ");
	while (buff && ft_strncmp(stop_str, buff, stop_str_len))
	{
		ft_putendl_fd(buff, fd[1]);
		free(buff);
		rl_on_new_line();
		buff = readline("> ");
	}
	if (buff)
		free(buff);
	close(fd[1]);
	dup2(current_fd, fd[0]);
	return (fd[0]);
}

int	append_stdout_to_file(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
	if (fd == -1)
	{
		g_ms.exit_code = 1;
		perror(filepath);
	}
	else
		dup2(fd, current_fd);
	return (fd);
}
