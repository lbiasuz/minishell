/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:44:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/27 14:05:18 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

static int	return_pipe_or_null(char **str_table, int index);
static char	**str_table_dup(char **parsed_input, int size);
static void	build_command(t_cmd *cmd);

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
		cmd->exe = NULL;
		cmd->exe_path = NULL;
		cmd->args = NULL;
		build_command(cmd);
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

static char	*filter_quotes(char *raw_str)
{
	if ('\'' == raw_str[0])
		return (ft_strtrim(raw_str, "\'"));
	if ('\"' == raw_str[0])
		raw_str = ft_strtrim(raw_str, "\"");
	else
		raw_str = ft_strdup(raw_str);
	return (replace_env_variables(raw_str));
}

static void	build_command(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->exe = NULL;
	while (cmd->raw[i] && ft_strncmp(cmd->raw[i], PIPE, sizeof(PIPE)))
	{
		if (is_redirect(cmd->raw[i]))
			i++;
		else if (!is_token(cmd->raw[i]) && !cmd->exe)
		{
			cmd->exe = replace_env_variables(ft_strdup(cmd->raw[i]));
			cmd->args = append_table(NULL, ft_strdup(cmd->exe));
		}
		else if (!is_token(cmd->raw[i]))
			cmd->args = append_table(cmd->args, filter_quotes(cmd->raw[i]));
		i++;
	}
	if (cmd->exe && (!ft_strchr(cmd->exe, '/') && cmd->exe[0] != '.'))
		cmd->exe_path = find_cmd_path(g_ms.envp, cmd->exe);
	else if (access(cmd->exe, X_OK) != -1)
		cmd->exe_path = ft_strdup(cmd->exe);
	else
		cmd->exe_path = NULL;
}
