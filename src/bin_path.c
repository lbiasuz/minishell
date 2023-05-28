/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:48:46 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/19 12:10:29 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_path(char *before, char *variable, char *after)
{
	char	*join1;
	char	*join2;

	if (!before)
		before = "";
	if (!variable)
		variable = "";
	if (!after)
		after = "";
	join1 = ft_strjoin(before, variable);
	join2 = ft_strjoin(join1, after);
	free(join1);
	return (join2);
}

char	*find_cmd_path(char **env, char	*command)
{
	char	**path_arr;
	char	*cmd_path;
	char	*path_value;
	int		index;

	index = 0;
	path_value = get_value(env, "PATH");
	if (!path_value)
		return (NULL);
	path_arr = ft_split(path_value, ':');
	free(path_value);
	while (path_arr[index])
	{
		cmd_path = join_path(path_arr[index], "/", command);
		if (access(cmd_path, X_OK) != -1)
			break ;
		free(cmd_path);
		index++;
	}
	if (!path_arr[index])
		cmd_path = NULL;
	free_table(path_arr);
	free(path_arr);
	return (cmd_path);
}

