/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:03:55 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/15 21:49:22 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../env.h"

t_ms	g_ms;

static void	print_export(char **envp);

int	export(char **argv)
{
	int		i;
	char	**envp;

	envp = g_ms.envp;
	i = 0;
	while (argv[i])
		i++;
	if (i <= 1)
		print_export(envp);
	else
	{
		i = 1;
		while (argv[i])
		{
			if (ft_strchr(argv[i], '='))
				envp = set_value(envp, ft_strdup(argv[i]));
			i++;
		}
		g_ms.envp = envp;
	}
	return (0);
}

static void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("export -x %s\n", envp[i]);
		i++;
	}
}
