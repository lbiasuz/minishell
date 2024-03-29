/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 01:02:37 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/01 10:51:07 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_end_of_prompt(char *prompt, int quotes_flag)
{
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
		else if (ft_strchr("|<>\'\"", prompt[0]) || ft_isspace(prompt[0]))
			break ;
		prompt++;
	}
	return (prompt);
}

static int	print_syntax_error(char *error)
{
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
	return (1);
}

static int	is_pipe(char *str)
{
	return (!ft_strncmp(str, PIPE, sizeof(PIPE)));
}

int	syntax_analize(char **input)
{
	int		index;
	char	*error;

	error = NULL;
	index = 0;
	while (input[index])
	{
		if (is_pipe(input[index]) && index == 0)
			error = PIPE;
		else if (is_pipe(input[index]) && !input[index + 1])
			error = "'newline'";
		else if (is_pipe(input[index]) && is_pipe(input[index + 1]))
			error = PIPE;
		else if (is_redirect(input[index]) && !input[index + 1])
			error = "'newline'";
		else if (is_redirect(input[index]) && is_redirect(input[index + 1]))
			error = input[index + 1];
		else if (is_redirect(input[index]) && is_pipe(input[index + 1]))
			error = PIPE;
		if (error && print_syntax_error(error))
			return (0);
		index++;
	}
	return (1);
}
