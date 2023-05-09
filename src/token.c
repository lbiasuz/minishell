/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:44:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/09 18:01:27 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**return_pipe_or_null(char **str_table);

t_list	*tokenize(char **parsed_input)
{
	char	**temp;
	t_cmd	*cmd;
	t_list	*cmd_list;

	cmd_list = NULL;
	while (parsed_input)
	{
		cmd = (t_cmd *) ft_calloc(sizeof(t_cmd), 1);
		if (!cmd)
			return (NULL);
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
		cmd->raw = parsed_input;
		temp = return_pipe_or_null(parsed_input);
		if (temp)
			cmd->raw_size = temp - parsed_input;
		else
			cmd->raw_size = ft_strlen((const char *) parsed_input);
		parsed_input = temp + 1;
	}
	return (cmd_list);
}

static char	**return_pipe_or_null(char **str_table)
{
	while (str_table[0])
	{
		if (!ft_strncmp(str_table[0], PIPE, sizeof(PIPE)))
			break ;
		str_table++;
	}
	return (str_table);
}