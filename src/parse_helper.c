/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 01:02:37 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/29 11:29:40 by lbiasuz          ###   ########.fr       */
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

int	syntax_analize(char **input)
{
	int		index;
	char	*error;

	error = NULL;
	index = 0;
	while (input[index])
	{
		if (!ft_strncmp(input[index], PIPE, sizeof(PIPE)) && index == 0)
			error = PIPE;
		if (!ft_strncmp(input[index], PIPE, sizeof(PIPE)) && !input[index + 1])
			error = "'newline'";
		else if (is_redirect(input[index]) && !input[index + 1])
			error = "'newline'";
		else if (is_redirect(input[index]) && is_redirect(input[index + 1]))
			error = input[index + 1];
		else if (is_redirect(input[index])
			&& !ft_strncmp(input[index + 1], PIPE, sizeof(PIPE)))
			error = PIPE;
		if (error)
		{
			ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
			ft_putstr_fd(error, STDERR_FILENO);
			ft_putendl_fd(";", STDERR_FILENO);
			return (0);
		}
		index++;
	}
	return (1);
}
