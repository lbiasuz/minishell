/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:48:46 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/04 18:45:33 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>

char	*find_cmd_path(char **env, char	*command)
{
	char	**path_arr;
	char	*cmd_path;
	int		index;

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
