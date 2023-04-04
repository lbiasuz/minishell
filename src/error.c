/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:20:00 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/03 21:35:54 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/token.h"

char	*get_token(t_list *node)
{
	if (node && node->content)
	{
		return (((t_tkn *) node->content)->token);
	}
	return (NULL);
}

char	*lookfor_error(t_list *tokens)
{
	t_list	*aux;

	aux = tokens;
	while (aux && aux->next)
	{
		if ((!ft_strncmp(get_token(aux), CHEV, sizeof(CHEV))
				&& !ft_strncmp(get_token(aux->next), CHEV, sizeof(CHEV)))
			|| (!ft_strncmp(get_token(aux), ICHEV, sizeof(ICHEV))
				&& !ft_strncmp(get_token(aux->next), ICHEV, sizeof(ICHEV)))
		)
			;
		else if (
			!ft_strncmp(get_token(aux), ERROR, sizeof(ERROR))
			|| (aux->next != NULL
				&& ft_strchr("<>\"\'|$&~", get_token(aux)[0])
				&& ft_strchr("<>\"\'|$&~", get_token(aux->next)[0]))
		)
			return (
				ft_strjoin(get_token(aux), get_token(aux->next))
			);
		aux = aux->next;
	}
	return (NULL);
}
