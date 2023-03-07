/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:52:40 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/07 11:40:07 by lbiasuz          ###   ########.fr       */
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
	envp = copy_environment(envp);
	g_ms.envp = envp;
	unset(argv);
	assert(g_ms.envp != envp);
	assert(g_ms.envp[0] == envp[0]);
	assert(!get_value(g_ms.envp, "USER"));
	free(g_ms.envp);
	cast_away(&argc);
	return (0);
}
