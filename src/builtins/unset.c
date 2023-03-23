/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:24:23 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/21 21:36:40 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env.h"

extern t_ms	g_ms;

int	unset(char **argv)
{
	int		i;
	char	*key;
	char	**envp;

	envp = g_ms.envp;
	i = 0;
	while (argv[i])
	{
		key = ft_strjoin(argv[i], "=");
		envp = unset_value(envp, key);
		free(key);
		i++;
	}
	g_ms.envp = envp;
	return (0);
}
