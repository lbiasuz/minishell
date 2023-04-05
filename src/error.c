/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 10:20:00 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/05 12:27:14 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

char	*get_token(t_list *node)
{
	if (node && node->content)
	{
		return (((t_tkn *) node->content)->token);
	}
	return (NULL);
}

void	join_tokens(t_list *t0, t_list *t1, t_list *t2)
{
	t_tkn	*new_token;
	t_list	*new_node;

	if (!t1 || !t2)
		return ;
	new_token = ft_calloc(1, sizeof(t_tkn));
	new_token->token = ft_strjoin(((t_tkn *) t1->content)->token, ((t_tkn *) t2->content)->token);
	new_token->value = ft_strjoin(((t_tkn *) t1->content)->value, ((t_tkn *) t2->content)->token);
	new_node = ft_calloc(1, sizeof(t_list));
	t0->next = new_node;
	new_node->next = t2->next;
	new_node->content = new_token;
	free(((t_tkn *) t2->content)->value);
	free(t2->content);
	free(((t_tkn *) t1->content)->value);
	free(t1->content);
}

char	*lookfor_error(t_list *tokens)
{
	t_list	*aux;
	t_list	*before;

	aux = tokens;
	while (aux && aux->next)
	{
		if ((!ft_strncmp(get_token(aux), CHEV, sizeof(CHEV))
				&& !ft_strncmp(get_token(aux->next), CHEV, sizeof(CHEV)))
			|| (!ft_strncmp(get_token(aux), ICHEV, sizeof(ICHEV))
				&& !ft_strncmp(get_token(aux->next), ICHEV, sizeof(ICHEV)))
		)
			join_tokens(before, aux, aux->next);
		else if (
			!ft_strncmp(get_token(aux), ERROR, sizeof(ERROR))
			|| (aux->next != NULL
				&& ft_strchr("<>\"\'|$&~", get_token(aux)[0])
			&& ft_strchr("<>\"\'|$&~", get_token(aux->next)[0]))
		)
			return (
				ft_strjoin(get_token(aux), get_token(aux->next))
			);
		before = aux;
		aux = aux->next;
	}
	return (NULL);
}
