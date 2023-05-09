/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:44:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/09 11:51:41 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*tokenize(char ***inputs)
{
	int		index;
	t_list	*cmd_list;
	t_cmd	*cmd;

	index = 0;
	cmd_list = NULL;
	while(*inputs[index])
	{
		cmd = (t_cmd *) ft_calloc(sizeof(t_cmd), 1);
		cmd->raw = (char **) ft_calloc(sizeof(char *), index);
		ft_memcpy(cmd->raw, &((*inputs)[index]), sizeof(char *) * index)
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
		index = return_pipe_or_null(*inputs, index);
	}
	return (cmd_list);
}
