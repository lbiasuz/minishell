/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:33:13 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/02/26 18:36:13 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../env.h"
#include <assert.h>

void	*cast_away(void *unused)
{
	return ((void *) unused);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*new_variable;
	char	**new_table;

	i = 0;
	envp = copy_environment(envp);
	new_variable = ft_strdup("HELLO=WORLD");
	new_table = set_value(envp, &new_variable);
	while (new_table[i] == envp[i])
		i++;
	assert(new_table[i] != NULL);
	assert(new_table[i] == new_variable);
	cast_away(&argc);
	cast_away(argv);
	return (0);
}
