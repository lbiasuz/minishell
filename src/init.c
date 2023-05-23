/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:57:05 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/15 09:53:55 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ms	init_minishell(char **env)
{
	t_ms	ms;

	ms.envp = copy_environment(env);
	ms.exit_code = 0;
	ms.commands = NULL;
	return (ms);
}
