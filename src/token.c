/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:44:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/10 09:00:29 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**return_pipe_or_null(char **str_table);
static char	**str_table_dup(char **parsed_input, int size);

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
		temp = return_pipe_or_null(parsed_input);
		cmd->raw = str_table_dup(parsed_input, temp - parsed_input);
		if (!cmd->raw)
			return (NULL);
		parsed_input = ++temp;
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
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

static char	**str_table_dup(char **parsed_input, int size)
{
	char	**dupped_table;

	if (size <= 0)
		size = sizeof(parsed_input);
	dupped_table = calloc(sizeof(char **), size);
	if (!dupped_table)
		return (NULL);
	while (--size >= 0)
		dupped_table[size] = ft_strdup(parsed_input[size]);
	return (dupped_table);
}