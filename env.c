/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:15:47 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/14 20:35:37 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft/ft_printf.h"

char	**copy_environment(char **env)
{
	int		table_size;
	char	**env_new_address;

	table_size = 0;
	while (env[table_size])
		table_size++;
	env_new_address = ft_calloc(table_size + 1, sizeof(char *));
	while (table_size-- > 0)
		env_new_address[table_size] = ft_strdup(env[table_size]);
	return (env_new_address);
}

char	**set_value(char **env, char **variable)
{
	int		table_size;
	char	**env_new_address;

	table_size = 0;
	env_new_address = update_value(env, variable);
	if (!env_new_address)
	{
		while (env[table_size])
			table_size++;
		env_new_address = ft_calloc(table_size + 2, sizeof(char *));
		ft_memmove(env_new_address, env, sizeof(char *) * (table_size + 1));
		env_new_address[table_size] = *variable;
		env_new_address[table_size + 1] = NULL;
		free(env);
	}
	return (env_new_address);
}

char	**unset_value(char **env, char *key)
{
	int		table_size;
	int		variable_location;
	char	**env_new_address;

	table_size = 0;
	variable_location = -1;
	env_new_address = env;
	while (env[table_size])
	{
		if (!ft_strncmp(key, env[table_size], ft_strlen(key)))
			variable_location = table_size;
		table_size++;
	}
	if (variable_location >= 0)
	{
		env_new_address = ft_calloc(table_size - 1, sizeof(char *));
		while (table_size-- > variable_location)
			env_new_address[table_size - 1] = env[table_size];
		free(env[variable_location]);
		while (variable_location-- > 0)
			env_new_address[variable_location] = env[variable_location];
		free(env);
	}
	return (env_new_address);
}

char	**update_value(char **env, char **variable)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_substr(*variable, 0, ft_strchr(*variable, '=') - *variable);
	while (env[i])
	{
		if (ft_strncmp(key, env[i], ft_strlen(key)) == 0)
		{
			free(key);
			free(env[i]);
			env[i] = *variable;
			return (env);
		}
		i++;
	}
	free(key);
	return (NULL);
}

char	*get_value(char **env, char *key)
{
	int		i;
	int		start;
	char	*variable;

	i = 0;
	if (ft_strchr(key, '='))
		variable = ft_strdup(key);
	else
		variable = ft_strjoin(key, "=");
	while (env[i] && ft_strncmp(variable, env[i], ft_strlen(variable)))
		i++;
	free(variable);
	if (!env[i])
		return (NULL);
	start = ft_strchr(env[i], '=') - env[i] + 1;
	return (ft_substr(env[i], start, ft_strlen(ft_strchr(env[i], '=') + 1)));
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
}
