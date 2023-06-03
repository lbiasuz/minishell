/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:36:58 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/03 20:53:32 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

int	env(void)
{
	int	i;

	i = 0;
	while (g_ms.envp[i])
		ft_putendl_fd(g_ms.envp[i++], 1);
	return (0);
}
