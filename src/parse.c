/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:33:03 by rmiranda          #+#    #+#             */
/*   Updated: 2023/03/25 20:56:39 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#define SEPARATORS "&|$<>"

static int	count_table_size(char *prompt);
static char	*next_prompt_address(char *prompt);
static int	fill_parse_values(char **str_table, char *prompt);
static char	*get_value(char *str_start, char *str_end);

char	**parse(char	*prompt)
{
	char	**parse_result;
	int		table_size;

	while (*prompt && ft_isspace(*prompt))
		prompt++;
	table_size = count_table_size(prompt);
	if (!table_size)
		return (NULL);
	parse_result = ft_calloc(table_size, sizeof(char *));
	if (!parse_result)
	{
		perror("ft_calloc by parse");
		return (NULL);
	}
	// else
	// insert_free(parse_result);
	if (fill_parse_values(parse_result, prompt))
		return (NULL);
	return (parse_result);
}

static int	count_table_size(char *prompt)
{
	char	*next_prompt;
	int		counter;

	counter = 0;
	next_prompt = prompt;
	while (next_prompt && ++counter)
	{
		prompt = next_prompt;
		next_prompt = next_prompt_address(prompt);
	}
	if (!next_prompt && *prompt)
		return (0);
	return (counter);
}

static char	*next_prompt_address(char *prompt)
{
	int	double_quotes_flag;
	int	single_quotes_flag;

	double_quotes_flag = 0;
	single_quotes_flag = 0;
	if (!*prompt)
		return (NULL);
	if (ft_strchr(SEPARATORS, *prompt))
		return (++prompt);
	if (ft_strchr("\"", *prompt))
		double_quotes_flag = 1;
	else if (ft_strchr("\'", *prompt))
		single_quotes_flag = 1;
	prompt++;
	while (*prompt)
	{
		if (ft_strchr(SEPARATORS, *prompt) && !(double_quotes_flag || single_quotes_flag))
			break ;
		if (ft_isspace(*prompt) && !(double_quotes_flag || single_quotes_flag))
			break ;
		if (ft_strchr("\"", *prompt) && double_quotes_flag)
		{
			double_quotes_flag--;
			prompt++;
			break ;
		}
		if (ft_strchr("\'", *prompt) && single_quotes_flag)
		{
			single_quotes_flag--;
			prompt++;
			break ;
		}
		prompt++;
	}
	while (*prompt && ft_isspace(*prompt))
		prompt++;
	if (double_quotes_flag || single_quotes_flag)
	{
		ft_printf("ERROR unclosed quotes\n");
		return (NULL);
	}
	return (prompt);
}

static int	fill_parse_values(char **str_table, char *prompt)
{
	char	*next_prompt;
	int		index;

	index = 0;
	next_prompt = next_prompt_address(prompt);
	while (next_prompt)
	{
		str_table[index] = get_value(prompt, next_prompt);
		if (!str_table[index])
			return (-1);
		prompt = next_prompt;
		next_prompt = next_prompt_address(prompt);
		index++;
	}
	return (0);
}

static char	*get_value(char *str_start, char *str_end)
{
	char	*value;
	int		str_len;

	str_len = str_end - str_start;
	while (ft_isspace(str_start[str_len - 1]))
		str_len--;
	value = ft_calloc(str_len + 1, sizeof(char *));
	if (!value)
	{
		perror("ft_calloc by get_vallue by fill_parse_values");
		return (NULL);
	}
	// else
	// 	insert_free(value);
	ft_memcpy(value, str_start, str_len);
	return (value);
}
