/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:48:46 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/17 12:07:18 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*find_cmd_path(char **env, char	*command)
{
	char	**path_arr;
	char	*cmd_path;
	int		index;

	if (!command)
		return (NULL);
	index = 0;
	path_arr = ft_split(get_value(env, "PATH"), ':');
	while (path_arr[index])
	{
		cmd_path = ft_strjoin(path_arr[index], command);
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
