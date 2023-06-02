/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:03:55 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/01 21:12:33 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

static void	print_export(char **envp);

static void	print_error(char *str)
{
	write(2, "export: ", ft_strlen("export: "));
	write(2, str, ft_strlen(str));
	write(2, ERROR_II, ft_strlen(ERROR_II));
	g_ms.exit_code = 1;
}

int	export(char **argv)
{
	int		i;

	g_ms.exit_code = 0;
	i = 0;
	while (argv[i])
		i++;
	if (i <= 1)
		print_export(g_ms.envp);
	else
	{
		i = 1;
		while (argv[i])
		{
			if (ft_isdigit(argv[i][0]))
				print_error(argv[i]);
			else if (ft_strchr(argv[i], '='))
				g_ms.envp = set_value(g_ms.envp, ft_strdup(argv[i]));
			i++;
		}
	}
	return (g_ms.exit_code);
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
