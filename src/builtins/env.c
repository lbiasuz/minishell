/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 08:36:58 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/04 20:05:26 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>

extern t_ms	g_ms;

int	env(void)
{
	int	i;

	i = 0;
	while (g_ms.envp[i++])
		ft_printf("%s\n", g_ms.envp[i]);
	exit(0);
}
