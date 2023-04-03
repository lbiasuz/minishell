/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:20:00 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/03 11:03:20 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/token.h"

t_tkn	*get_token(t_list *node)
{
	if (node && node->content)
	{
		return ((t_tkn *) node->content);
	}
	return (NULL);
}

char	*lookfor_error(t_list *tokens)
{
	t_list	*aux;

	aux = tokens;
	while (aux)
	{
		if ((ft_strncmp(get_token(aux)->token, CHEV, sizeof(CHEV))
				&& ft_strncmp(get_token(aux)->token, CHEV, sizeof(CHEV)))
			|| (ft_strncmp(get_token(aux)->token, ICHEV, sizeof(ICHEV))
				&& ft_strncmp(get_token(aux)->token, ICHEV, sizeof(ICHEV)))
			|| ft_strncmp(get_token(aux)->token, TEXT, sizeof(TEXT))
			|| ft_strncmp(get_token(aux)->token, EXPAND, sizeof(EXPAND))
		)
			continue ;
		if (
			ft_strncmp(get_token(aux)->token, ERROR, sizeof(ERROR))
			|| (aux->next != NULL
				&& ft_strchr("<>\"\'|$&~", get_token(aux)->token[0])
				&& ft_strchr("<>\"\'|$&~", get_token(aux->next)->token[0]))
		)
			return (
				ft_strjoin(get_token(aux)->token, get_token(aux->next)->token)
			);
		aux = aux->next;
	}
	return (NULL);
}
