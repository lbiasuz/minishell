/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:15:48 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/15 20:58:35 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <assert.h>

extern t_ms	g_ms;

void	*cast_away(void *unused)
{
	return ((void *) unused);
}

int	main(int argc, char **argv, char **envp)
{
	char	*result;

	envp = copy_environment(envp);
	argv = copy_environment(argv);
	g_ms.envp = envp;
	export(argv);
	result = get_value(g_ms.envp, "USER");
	assert(result);
	free(result);
	result = get_value(g_ms.envp, "HELLO");
	assert(!result);
	free(result);
	free_table(g_ms.envp);
	free_table(argv);
	free(argv);
	free(g_ms.envp);
	cast_away(&argc);
	return (0);
}
