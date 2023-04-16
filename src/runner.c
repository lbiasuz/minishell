/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/16 09:50:45 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms g_ms;

char	*get_command(t_list *list)
{
	t_list	*node;
	t_list	*last_node;

	node = list;
	while (node && ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
	{
		if (ft_strncmp(gtkn(last_node), DICHEV, sizeof(DICHEV))
			&& ft_strncmp(gtkn(last_node), DCHEV, sizeof(DCHEV))
			&& ft_strncmp(gtkn(last_node), CHEV, sizeof(CHEV))
			&& ft_strncmp(gtkn(last_node), ICHEV, sizeof(ICHEV))
			&& (!ft_strncmp(gtkn(node), EXPAND, sizeof(EXPAND))
				|| !ft_strncmp(gtkn(node), TEXT, sizeof(TEXT))
				|| !ft_strncmp(gtkn(node), SQUOTE, sizeof(SQUOTE))
				|| !ft_strncmp(gtkn(node), DQUOTE, sizeof(DQUOTE))))
			return (find_cmd_path(g_ms.envp, gvle(node)));
		last_node = node;
		node = node->next;
	}
	return (NULL);
}

char	**get_args(t_list *list)
{
	t_list	*node;
	t_list	*last_node;
	char	**args;

	args = NULL;
	node = list;
	while (node && ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
	{
		if ((!ft_strncmp(gtkn(node), EXPAND, sizeof(EXPAND))
				|| !ft_strncmp(gtkn(node), TEXT, sizeof(TEXT))
				|| !ft_strncmp(gtkn(node), SQUOTE, sizeof(SQUOTE))
				|| !ft_strncmp(gtkn(node), DQUOTE, sizeof(DQUOTE)))
			&& (!ft_strncmp(gtkn(last_node), EXPAND, sizeof(EXPAND))
				|| !ft_strncmp(gtkn(last_node), TEXT, sizeof(TEXT))
				|| !ft_strncmp(gtkn(last_node), SQUOTE, sizeof(SQUOTE))
				|| !ft_strncmp(gtkn(last_node), DQUOTE, sizeof(DQUOTE))))
			args = append_table(args, gvle(node));
		last_node = node;
		node = node->next;
	}
	return (args);
}

void	invoke_child(t_list *tokens, int in_fd, int out_fd)
{
	redirect_fds(tokens, in_fd, out_fd);
	execve(get_command(tokens), get_args(tokens), g_ms.envp);
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
	if (pid == 0)
		exit(0);
}
