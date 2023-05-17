/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:50:14 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/17 19:37:39 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
}

char	**pop_table(char **table, char *address)
{
	int		i;
	char	**new_table;

	i = 0;
	while (table && table[i])
		i++;
	new_table = (char **) ft_calloc(i, sizeof(char *));
	while (table[--i] != address)
		new_table[i - 1] = table[i];
	if (table)
	{
		ft_memmove(new_table, table, sizeof(char *) * (i - 1));
		free(table);
	}
	free(address);
	return (new_table);
}

char	**append_table(char	**table, char *variable)
{
	int		i;
	char	**new_address;

	i = 0;
	while (table && table[i])
		i++;
	new_address = (char **) ft_calloc(i + 2, sizeof(char *));
	if (table)
	{
		ft_memmove(new_address, table, sizeof(char *) * (i + 1));
		free(table);
	}
	new_address[i] = variable;
	new_address[i + 1] = NULL;
	return (new_address);
}
