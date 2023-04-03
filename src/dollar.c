/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:00:36 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/03 10:49:58 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/env.h"

extern t_ms	g_ms;

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

int	expand_dollar_sign(char *input, char *dollar)
{
	char	**occurences;
	int		flag;
	int		index;

	occurences = char_occurences(input, '\'');
	index = 0;
	while (occurences[index] && occurences[index] < dollar)
		index++;
	if (occurences[index] && index % 2 == 0)
		flag = 1;
	else
		flag = 0;
	free(occurences);
	return (flag);
}

char	*join_envp_var(char *variable, char *before, char *after)
{
	char	*join1;
	char	*join2;

	join1 = ft_strjoin(before, variable);
	join2 = ft_strjoin(join1, after);
	free(join1);
	return (join2);
}

char	*expand_variable(char *input, char *dollar)
{
	int		index;
	char	*variable;
	char	*value;

	index = 0;
	while (ft_isalnum(dollar[index]) || dollar[index] == '_')
		index++;
	variable = ft_substr(dollar, 1, index);
	value = get_value(g_ms.envp, variable);
	return (join_envp_var(
			ft_substr(input, 0, dollar - input),
			value,
			ft_substr(&input[index], 0, ft_strlen(&input[index]))
		)
	);
}
