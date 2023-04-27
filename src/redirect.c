/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:23:22 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/27 19:03:41 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_fds(t_list *tokens, int fd[2], int ofd[2])
{
	t_list	*node;

	node = tokens;
	while (node)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
			break ;
		if (!ft_strncmp(gtkn(node), DICHEV, sizeof(DICHEV)))
			ofd[0] = heredoc_to_stdin(gvle(node->next), ofd[0]);
		else if (!ft_strncmp(gtkn(node), DCHEV, sizeof(DCHEV)))
			fd[1] = append_stdout_to_file(gvle(node->next), fd[1]);
		else if (!ft_strncmp(gtkn(node), CHEV, sizeof(CHEV)))
			fd[1] = stdout_to_file(gvle(node->next), fd[1]);
		else if (!ft_strncmp(gtkn(node), ICHEV, sizeof(ICHEV)))
			ofd[0] = file_to_stdin(gvle(node->next), ofd[0]);
		node = node->next;
	}
	if (!return_pipe_or_null(tokens))
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	}
	else
	{
		dup2(ofd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
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
	return (fd);
}
