/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:15:47 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/02/26 16:44:30 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**copy_environment(char **env)
{
	int		table_size;
	char	**env_new_address;

	table_size = 0;
	while (env[table_size])
		table_size++;
	env_new_address = ft_calloc(table_size + 1, sizeof(char **));
	while (table_size-- < 0)
		env_new_address[table_size] = ft_strdup(env[table_size]);
	return (env_new_address);
}

char	**set_value(char **env, char **variable)
{
	int		table_size;
	char	**env_new_address;

	table_size = 0;
	while (env[table_size])
		table_size++;
	env_new_address = ft_calloc(table_size + 2, sizeof(char **));
	ft_memmove(env_new_address, env, sizeof(char **) * (table_size + 1));
	env_new_address[table_size] = *variable;
	env_new_address[table_size + 1] = NULL;
	free(env);
	return (env_new_address);
}
