/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:44:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/15 20:57:39 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*plain_token(char *input)
{
	t_tkn	*token;

	token = (t_tkn *)ft_calloc(1, sizeof(t_tkn));
	if (!ft_strncmp(input, PIPE, sizeof(input)))
		token->token = PIPE;
	else if (!ft_strncmp(input, CHEV, sizeof(input)))
		token->token = CHEV;
	else if (!ft_strncmp(input, ICHEV, sizeof(input)))
		token->token = ICHEV;
	else if (!ft_strncmp(input, ECOM, sizeof(input)))
		token->token = ECOM;
	else if (!ft_strncmp(input, HOME, sizeof(input)))
		token->token = EXPAND;
	else
		token->token = TEXT;
	token->value = ft_strdup(input);
	return (ft_lstnew(token));
}

t_list	*compose_token(char *input)
{
	t_tkn	*token;

	token = (t_tkn *)ft_calloc(1, sizeof(t_tkn));
	if (ft_strchr(input, '$'))
		token->token = EXPAND;
	else if (ft_strchr(input, '\"'))
		token->token = DQUOTE;
	else
		token->token = TEXT;
	token->value = ft_strdup(input);
	return (ft_lstnew(token));
}

t_list	*tokenize(char **inputs)
{
	t_list	*token_list;
	int		len;
	int		index;

	index = 0;
	token_list = NULL;
	while (inputs[index])
	{
		len = ft_strlen(inputs[index]);
		if (len == 1 && inputs[index][0] && !ft_isalnum(inputs[index][0]))
			ft_lstadd_back(&token_list, plain_token(inputs[index]));
		else
			ft_lstadd_back(&token_list, compose_token(inputs[index]));
		index++;
	}
	return (token_list);
}
