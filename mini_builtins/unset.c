/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:24:23 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/03 10:58:25 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../env.h"

int	unset(int argc, char **argv, char **envp)
{
	int		i;
	char	**key;
	
	i = 0;
	while (argv[i])
	{
		key = ft_strjoin(argv[i], "=");
		envp = unset_value(envp, key);
		free(key);
	}
	return (0);
}