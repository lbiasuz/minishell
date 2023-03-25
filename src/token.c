/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:44:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/24 10:30:50 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"



t_list	*tokenize(char *input)
{
	t_list	*token;
	int		len;
	
	len = ft_strlen(input);
	if (len == 1)
		return (plain_token(input))
	else if (len == 2 && !ft_isalnum(input[0]) && !ft_isalnum(input[1]))
		return (plain_token(input))
	
	
	return (token);
}