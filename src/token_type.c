/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:18:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/04 22:29:46 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_redirect(char *token)
{
	if (!token)
		return (0);
	return (!ft_strncmp(token, DICHEV, sizeof(DICHEV))
		|| !ft_strncmp(token, DCHEV, sizeof(DCHEV))
		|| !ft_strncmp(token, CHEV, sizeof(CHEV))
		|| !ft_strncmp(token, ICHEV, sizeof(ICHEV)));
}

int	is_command(char	*token, char *last_token)
{
	if (!token)
		return (0);
	return ((!last_token || !is_redirect(last_token))
		&& (!ft_strncmp(token, EXPAND, sizeof(EXPAND))
			|| !ft_strncmp(token, TEXT, sizeof(TEXT))
			|| !ft_strncmp(token, SQUOTE, sizeof(SQUOTE))
			|| !ft_strncmp(token, DQUOTE, sizeof(DQUOTE)))
	);
}
