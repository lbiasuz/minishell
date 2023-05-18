/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:33:03 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/18 19:49:01 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define SINGLE_QUOTES 1
#define DOUBLE_QUOTES 2

static int	count_table_size(char *prompt);
static char	*next_prompt_address(char *prompt);
static int	fill_parse_values(char **str_table, char *prompt);
static char	*get_value_prompt(char *str_start, char *str_end);

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
	int	quotes_flag;

	if (!prompt[0])
		return (NULL);
	if (ft_strchr("&|<>", prompt[0]))
	{
		if (!ft_strncmp(">>", prompt, 2) || !ft_strncmp("<<", prompt, 2))
			prompt += 2;
		else
			prompt++;
		while (prompt[0] && ft_isspace(prompt[0]))
			prompt++;
		return (prompt);
	}
	quotes_flag = 0;
	if (ft_strchr("\"", prompt[0]))
		quotes_flag = DOUBLE_QUOTES;
	else if (ft_strchr("\'", prompt[0]))
		quotes_flag = SINGLE_QUOTES;
	prompt++;
	while (prompt[0])
	{
		if (quotes_flag)
		{
			if (quotes_flag == DOUBLE_QUOTES && ft_strchr("\"", prompt[0])
				&& quotes_flag-- && ++prompt)
				break ;
			if (quotes_flag == SINGLE_QUOTES && ft_strchr("\'", prompt[0])
				&& quotes_flag-- && ++prompt)
				break ;
		}
		else if (ft_strchr("&|$<>\'\"", prompt[0]) || ft_isspace(prompt[0]))
			break ;
		prompt++;
	}
	while (prompt[0] && ft_isspace(prompt[0]))
		prompt++;
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
		str_table[index] = get_value_prompt(prompt, next_prompt);
		if (!str_table[index])
			return (-1);
		prompt = next_prompt;
		next_prompt = next_prompt_address(prompt);
		index++;
	}
	return (0);
}

static char	*get_value_prompt(char *str_start, char *str_end)
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
	ft_memcpy(value, str_start, str_len);
	return (value);
}
