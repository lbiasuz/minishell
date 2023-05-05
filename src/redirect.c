/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:23:22 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/04 22:26:03 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	close_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

void	redirect_fds(t_list *tokens, t_cmd cmd, int fd[2], int ofd[2])
{
	cmd.file_in = ofd[0];
	cmd.file_out = fd[1];
	while (tokens && !ft_strncmp(gtkn(tokens), PIPE, sizeof(PIPE)))
	{
		if (!ft_strncmp(gtkn(tokens), ICHEV, sizeof(ICHEV)))
			cmd.file_in = file_to_stdin(gvle(tokens->next), ofd[0]);
		else if (!ft_strncmp(gtkn(tokens), DICHEV, sizeof(DICHEV)))
			cmd.file_in = heredoc_to_stdin(gvle(tokens->next), ofd[0]);
		else if (!ft_strncmp(gtkn(tokens), CHEV, sizeof(CHEV)))
			cmd.file_out = stdout_to_file(gvle(tokens->next), fd[1]);
		else if (!ft_strncmp(gtkn(tokens), DCHEV, sizeof(DCHEV)))
			cmd.file_out = append_stdout_to_file(gvle(tokens->next), fd[1]);
		tokens = tokens->next;
	}
	if (!return_pipe_or_null(tokens))
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	else
		dup2(cmd.file_out, STDOUT_FILENO);
	dup2(cmd.file_in, STDIN_FILENO);
	close_fd(ofd[1]);
	close_fd(ofd[0]);
	close_fd(fd[0]);
	close_fd(fd[1]);
}

int	file_to_stdin(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		perror("File not found");
		return (fd);
	}
	dup2(fd, current_fd);
	close(current_fd);
	return (fd);
}

int	stdout_to_file(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		perror("File not found");
		return (fd);
	}
	dup2(fd, current_fd);
	close(current_fd);
	return (fd);
}

int	heredoc_to_stdin(char *stop_str, int current_fd)
{
	char	*buff;
	int		stop_str_len;

	buff = "";
	stop_str_len = ft_strlen(stop_str);
	while (ft_strncmp(stop_str, buff, stop_str_len))
	{
		rl_on_new_line();
		buff = readline("heredoc> ");
		if (!buff)
			return (-1);
		write(current_fd, buff, ft_strlen(buff));
		free(buff);
	}
	if (buff)
		free(buff);
	return (0);
}

int	append_stdout_to_file(char *filepath, int current_fd)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
	{
		perror("File not found");
		return (fd);
	}
	dup2(fd, current_fd);
	close(current_fd);
	return (fd);
}
