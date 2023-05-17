/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:44:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/17 19:35:19 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	return_pipe_or_null(char **str_table, int index);
static char	**str_table_dup(char **parsed_input, int size);

t_list	*build_cmd_list(char **parsed_input)
{
	t_cmd	*cmd;
	t_list	*cmd_list;
	int		index;
	int		next_index;

	index = 0;
	cmd_list = NULL;
	while (parsed_input[index])
	{
		cmd = (t_cmd *) ft_calloc(sizeof(t_cmd), 1);
		next_index = return_pipe_or_null(parsed_input, index);
		cmd->raw = str_table_dup(&parsed_input[index], next_index - index);
		cmd->fd[0] = 0;
		cmd->fd[1] = 1;
		if (parsed_input[next_index])
			index = ++next_index;
		else
			index = next_index;
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	}
	return (cmd_list);
}

static int	return_pipe_or_null(char **parse, int index)
{
	while (parse[index])
	{
		if (!ft_strncmp(parse[index], PIPE, sizeof(PIPE)))
			break ;
		index++;
	}
	return (index);
}

static char	**str_table_dup(char **parsed_input, int size)
{
	char	**dupped_table;

	dupped_table = ft_calloc(sizeof(char *), size + 1);
	dupped_table[size] = NULL;
	while (--size >= 0)
		dupped_table[size] = ft_strdup(parsed_input[size]);
	return (dupped_table);
}
