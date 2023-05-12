/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:21:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/12 15:48:32 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <libft.h>

t_cmd	*cast_cmd(t_list *node)
{
	if (node && node->content)
		return ((t_cmd *) node->content);
	return (NULL);
}

int	char_count(char *string, char c)
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

// void	free_command(void *cmd)
// {
// 	free(((t_cmd *) cmd));
// 	free(tkn);
// }

void	free_str_table(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		input[i] = NULL;
		i++;
	}
	free(input);
}
