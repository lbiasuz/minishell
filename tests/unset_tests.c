/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:52:40 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/07 23:18:44 by lbiasuz          ###   ########.fr       */
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
	g_ms.envp = copy_environment(envp);
	unset(argv);
	assert(g_ms.envp != envp);
	ft_printf("%s\n", g_ms.envp[0]);
	ft_printf("%s\n", envp[0]);
	assert(g_ms.envp[0] == envp[0]);
	assert(!get_value(g_ms.envp, "USER"));
	free(g_ms.envp);
	cast_away(&argc);
	return (0);
}
