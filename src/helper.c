/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:21:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/19 10:21:35 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <libft.h>

t_cmd	*cast_cmd(t_list *node)
{
	if (node && node->content)
		return ((t_cmd *) node->content);
	return (NULL);
}

void	close_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

void	free_node(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (cmd->exe)
		free(cmd->exe);
	if (cmd->exe_path)
		free(cmd->exe_path);
	if (cmd->args)
	{
		free_table(cmd->args);
		free(cmd->args);
	}
	if (cmd->raw)
	{
		free_table(cmd->raw);
		free(cmd->raw);
	}
	free(cmd);
}
