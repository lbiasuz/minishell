/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:54:46 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/08 20:53:11 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**syntax_error_location_or_null(char **parsed_input)
{
	int	pipe_allowed;
	int	chev_allowed;
	int	ecom_allowed;

	pipe_allowed = 0;
	chev_allowed = 0;
	ecom_allowed = 0;
	while (parsed_input)
	{
		if (pipe_allowed && ft_strncmp(parsed_input[0], DICHEV, sizeof(DICHEV)))
			return (parsed_input);
		if (chev_allowed && ft_strncmp(parsed_input[0], DICHEV, sizeof(DICHEV)))
			return (parsed_input);
		if (ecom_allowed && ft_strncmp(parsed_input[0], DICHEV, sizeof(DICHEV)))
			return (parsed_input);
	}
	return (NULL);
}

int	syntax_analysis(char **parsed_input)
{
	char	**error;

	error = syntax_error_location_or_null(parsed_input);
	if (error)
	{
		printf("syntax error: %s", error[0]);
		free_parse(parsed_input);
		return (-1);
	}
	return (0);
}
