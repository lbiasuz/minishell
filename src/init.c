/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:57:05 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/08 10:18:52 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>

t_ms	init_minishell(char **env)
{
	t_ms	ms;

	ms.cmdlist = NULL;
	ms.tokenlist = NULL;
	ms.envp = copy_environment(env);
	ms.exit_code = 0;
	return (ms);
}