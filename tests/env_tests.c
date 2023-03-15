/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:33:13 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/14 11:12:36 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../env.h"
#include <assert.h>

void	*cast_away(void *unused)
{
	return ((void *) unused);
}

static void	test_setvalue(char **envp)
{
	int		i;
	char	*new_variable;
	char	**new_table;

	i = 0;
	envp = copy_environment(envp);
	new_variable = ft_strdup("HELLO=WORLD");
	new_table = set_value(envp, &new_variable);
	while (new_table[i])
		i++;
	assert(new_table[i - 1] == new_variable);
	envp = unset_value(new_table, "HELLO=");
	new_variable = get_value(envp, "HELLO");
	assert(!new_variable);
	free(new_variable);
}

static void	test_updatevalue(char **envp)
{
	int		i;
	char	*new_variable;
	char	**new_table;

	i = 0;
	envp = copy_environment(envp);
	new_variable = ft_strdup("USER=coder");
	new_table = set_value(envp, &new_variable);
	while (new_table[i])
	{
		if (!ft_strncmp(new_table[i], "USER=", 5))
			break ;
		i++;
	}
	assert(new_table[i] == new_variable);
	free_env(new_table);
	free(new_variable);
}

int	main(int argc, char **argv, char **envp)
{
	test_setvalue(envp);
	test_updatevalue(envp);
	cast_away(&argc);
	cast_away(argv);
	return (0);
}
