/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:03:55 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/02 11:23:27 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../env.h"

int	export(int argc, char **argv, char **envp)
{
	int		i;
	char	***envp_address;

	if (argc <= 1)
		print_export(envp);
	else
	{
		i = 1;
		envp_address = &envp;
		while (argv[i])
		{
			if (ft_strchr(argv[i], '='))
				envp = set_value(envp, &argv[i]);
			i++;
		}
		envp_address = &envp;
	}
	return (0);
}

void	printe_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("export -x %s\n", envp[i]);
		i++;
	}
}
