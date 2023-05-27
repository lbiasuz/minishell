/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:23:22 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/26 10:17:21 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_single(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->raw[i] && ft_strncmp(cmd->raw[i], PIPE, sizeof(PIPE)))
	{
		if (!ft_strncmp(cmd->raw[i], ICHEV, sizeof(ICHEV)))
			cmd->fd[0] = file_to_stdin(cmd->raw[i + 1], cmd->fd[0]);
		else if (!ft_strncmp(cmd->raw[i], DICHEV, sizeof(DICHEV)))
			cmd->fd[0] = heredoc_to_stdin(cmd->raw[i + 1], cmd->fd[1]);
		else if (!ft_strncmp(cmd->raw[i], CHEV, sizeof(CHEV)))
			cmd->fd[1] = stdout_to_file(cmd->raw[i + 1], cmd->fd[1]);
		else if (!ft_strncmp(cmd->raw[i], DCHEV, sizeof(DCHEV)))
			cmd->fd[1] = append_stdout_to_file(cmd->raw[i + 1], cmd->fd[1]);
		i++;
	}
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
}

void	redirect_fds(t_cmd *cmd, t_cmd *next)
{
	int	i;

	i = 0;
	while (cmd->raw[i] && ft_strncmp(cmd->raw[i], PIPE, sizeof(PIPE)))
	{
		if (!ft_strncmp(cmd->raw[i], ICHEV, sizeof(ICHEV)))
			cmd->fd[0] = file_to_stdin(cmd->raw[i + 1], cmd->fd[0]);
		else if (!ft_strncmp(cmd->raw[i], DICHEV, sizeof(DICHEV)))
			cmd->fd[0] = heredoc_to_stdin(cmd->raw[i + 1], cmd->fd[1]);
		else if (next && !ft_strncmp(cmd->raw[i], CHEV, sizeof(CHEV)))
			next->fd[1] = stdout_to_file(cmd->raw[i + 1], next->fd[1]);
		else if (next && !ft_strncmp(cmd->raw[i], DCHEV, sizeof(DCHEV)))
			next->fd[1] = append_stdout_to_file(cmd->raw[i + 1], next->fd[1]);
		i++;
	}
	dup2(cmd->fd[0], STDIN_FILENO);
	if (next)
		dup2(next->fd[1], STDOUT_FILENO);
	close_fd(cmd->fd[1]);
}

int	file_to_stdin(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		perror(filepath);
		return (fd);
	}
	dup2(fd, current_fd);
	close(fd);
	return (fd);
}

int	stdout_to_file(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if (fd == -1)
		perror(filepath);
	else
		dup2(fd, current_fd);
	return (fd);
}

int	heredoc_to_stdin(char *stop_str, int current_fd)
{
	char	*buff;
	int		stop_str_len;
	int		fd[2];

	(void)current_fd;
	pipe(fd);
	stop_str_len = ft_strlen(stop_str);
	buff = readline("> ");
	while (ft_strncmp(stop_str, buff, stop_str_len))
	{
		ft_putendl_fd(buff, fd[1]);
		free(buff);
		rl_on_new_line();
		buff = readline("> ");
	}
	if (!buff)
		return (-1);
	free(buff);
	close(fd[1]);
	if (current_fd > 0)
		close(current_fd);
	return (fd[0]);
}

int	append_stdout_to_file(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
	if (fd == -1)
	{
		perror(filepath);
		return (fd);
	}
	dup2(fd, current_fd);
	return (fd);
}
