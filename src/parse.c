/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:33:03 by rmiranda          #+#    #+#             */
/*   Updated: 2023/03/23 21:45:42 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**parse(char	*prompt)
{
	char	**parse_result;

	parse_result = ft_split(prompt, ' ');
	return (parse_result);
}