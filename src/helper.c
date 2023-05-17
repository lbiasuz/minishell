/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:21:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/17 07:29:01 by rmiranda         ###   ########.fr       */
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

int	char_count(char *string, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (string[index])
	{
		if (string[index] == c)
			count++;
		index ++;
	}
	return (count);
}

char	**char_occurences(char *string, char c)
{
	char	*aux;
	int		index;
	char	**occurences;

	index = 0;
	aux = string;
	occurences = ft_calloc(char_count(string, c), sizeof(char **));
	while (string[index])
	{
		aux = ft_strchr(aux, c);
		occurences[index] = aux;
		index++;
	}
	return (occurences);
}

int	byp_builtin(char *cmd_str)
{
	if (!ft_strncmp(cmd_str, "cd", sizeof("cd"))
		|| !ft_strncmp(cmd_str, "echo", sizeof("echo"))
		|| !ft_strncmp(cmd_str, "env", sizeof("env"))
		|| !ft_strncmp(cmd_str, "exit", sizeof("exit"))
		|| !ft_strncmp(cmd_str, "export", sizeof("export"))
		|| !ft_strncmp(cmd_str, "pwd", sizeof("pwd"))
		|| !ft_strncmp(cmd_str, "unset", sizeof("unset")))
		return (1);
	return (0);
}

void	free_node_contents(void *content)
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
