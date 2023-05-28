/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 01:02:37 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/29 01:02:56 by rmiranda         ###   ########.fr       */
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
