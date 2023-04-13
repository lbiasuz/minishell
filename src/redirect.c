/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:23:22 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/13 11:47:29 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <redirect.h>
#include <token.h>

void	redirect_fds(t_list *tokens, int in_fd, int out_fd)
{
	t_list	*node;

	node = tokens;
	while (node && ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
	{
		if (!ft_strncmp(gtkn(node), DICHEV, sizeof(DICHEV)))
			in_fd = heredoc_to_stdin(gvle(node->next), in_fd);
		else if (!ft_strncmp(gtkn(node), DCHEV, sizeof(DCHEV)))
			out_fd = append_stdout_to_file(gvle(node->next), out_fd);
		else if (!ft_strncmp(gtkn(node), CHEV, sizeof(CHEV)))
			out_fd = stdout_to_file(gvle(node->next), out_fd);
		else if (!ft_strncmp(gtkn(node), ICHEV, sizeof(ICHEV)))
			in_fd = file_to_stdin(gvle(node->next), in_fd);
		node = node->next;
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
