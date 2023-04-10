/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:20:00 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/10 10:06:02 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

void	join_tokens(t_list *t1, t_list *t2)
{
	char	*join_value;
	char	*token_value;

	if (!t1 || !t2)
		return ;
	token_value = ft_strjoin(
			((t_tkn *) t1->content)->value, ((t_tkn *) t2->content)->token);
	join_value = ft_strjoin(
			((t_tkn *) t1->content)->token, ((t_tkn *) t2->content)->token);
	free(((t_tkn *) t1->content)->value);
	free(((t_tkn *) t2->content)->value);
	((t_tkn *) t1->content)->value = join_value;
	((t_tkn *) t1->content)->token = token_value;
	t1->next = t2->next;
	free(t2->content);
	free(t2);
}

char	*lookfor_error(t_list *tokens)
{
	t_list	*aux;

	aux = tokens;
	while (aux && aux->next)
	{
		if ((!ft_strncmp(gtkn(aux), CHEV, sizeof(CHEV))
				&& !ft_strncmp(gtkn(aux->next), CHEV, sizeof(CHEV)))
			|| (!ft_strncmp(gtkn(aux), ICHEV, sizeof(ICHEV))
				&& !ft_strncmp(gtkn(aux->next), ICHEV, sizeof(ICHEV)))
		)
			join_tokens(aux, aux->next);
		else if (
			!ft_strncmp(gtkn(aux), ERROR, sizeof(ERROR))
			|| (aux->next != NULL
				&& ft_strchr("<>\"\'|$&~", gtkn(aux)[0])
			&& ft_strchr("<>\"\'|$&~", gtkn(aux->next)[0]))
		)
			return (
				ft_strjoin(gtkn(aux), gtkn(aux->next))
			);
		aux = aux->next;
	}
	return (NULL);
}
