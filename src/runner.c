/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/12 12:11:28 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <redirect.h>
#include <token.h>
#include <env.h>
#include <unistd.h>

void	invoke_child(t_list *tokens, int in_fd, int out_fd)
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
	execve();
}




void	runner(t_list *token_list)
{
	t_list	*node;
	int		pid;
	int		old_fd[2];
	int		fd[2];

	node = token_list;
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	old_fd[0] = STDIN_FILENO;
	old_fd[1] = STDOUT_FILENO;
	pid = -1;
	while (pid != 0 && node)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)) && pid != 0)
		{
			old_fd[0] = fd[0];
			old_fd[1] = fd[1];
			pipe(fd);
			pid = fork();
		}
		else if (!node->next && pid != 0)
			pid = fork();
		node = node->next;
	}
	if (pid == 0 && node)
		invoke_child(node, old_fd[0], fd[1]);
	if (pid == 0 && !node)
		invoke_child(node, old_fd[0], STDOUT_FILENO);
}
