/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:00:36 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/27 21:24:23 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		char_count(char *string, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (string[index])
	{
		if (string[index] == c)
			count++;
		index ++;
	}
	return (count);
}

char	**char_occurences(char *string, char c)
{
	char	*aux;
	int		index;
	char	**occurences;

	index = 0;
	aux = string;
	occurences = ft_calloc(char_count(string, c), sizeof(char **));
	while (string[index])
	{
		aux = ft_strchr(aux, c);
		occurences[index] = aux;
		index++;
	}
	return (occurences);
}

int	expand_dollar_sign(char *input, char *dollar)
{
	char	**occurences;
	int		flag;
	int		index;
	
	occurences = char_occurences(input, '\'');
	index = 0;
	while(occurences[index] && occurences[index] < dollar)
		index++;
	if (occurences[index] && index % 2 == 0)
		flag = 1;
	else
		flag = 0;
	free(occurences);
	return (flag);
}