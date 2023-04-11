/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/11 11:40:57 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>
#include <env.h>
#include <unistd.h>

void	invoke_child(t_list *tokens, int in_fd, int out_fd);

void	runner(t_list *token_list)
{
	t_list	*node;
	int		pid;
	int		old_fd[2];
	int		fd[2];

	node = token_list;
	fd = {STDIN_FILENO, STDOUT_FILENO};
	old_fd = fd;
	pid = -1;
	while (pid != 0 && node)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)) && pid != 0)
		{
			old_fd = fd;
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
		invoke_child(node, old_fd[0], STDOUT_FILENO)
}
