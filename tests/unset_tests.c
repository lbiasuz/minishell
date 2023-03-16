/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:52:40 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/16 11:06:04 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include "../env.h"
#include <assert.h>

extern t_ms	g_ms;

void	*cast_away(void *unused)
{
	return ((void *) unused);
}

int	main(int argc, char **argv, char **envp)
{
	char *variable;

	(void)argc;
	g_ms.envp = copy_environment(envp);
	unset(argv);
	variable = get_value(g_ms.envp, "USER");
	assert(!variable);
	free(variable);
	free_env(g_ms.envp);
	free(g_ms.envp);
	return (0);
}
