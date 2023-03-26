/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:44:31 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/26 10:53:20 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"

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
	token->value = input;
	return (ft_lstnew(token));
}

t_list	*compose_token(char *input)
{
	t_tkn	*token;
	char	*addr;

	token = (t_tkn *)ft_calloc(1, sizeof(t_tkn));
	addr = ft_strchr(input, '$');
	if (addr && char_occurences(input, '\'') % 2 == 0
		&& (ft_strchr(input, '\''))
		&& (ft_strchr(input, '\'') > addr || ft_strrchr(input, '\'') < addr))
		token->token = EXPAND;
	else if (char_occurences(input, '\'') > 1)
		token->token = SQUOTE;	
	else if (char_occurences(input, '\"') > 1)
		token->token = DQUOTE;
	else if (addr)
		token->token = EXPAND;
	else
		token->token = TEXT;
	token->value = input;
	return (ft_lstnew(token));
}

t_list	*tokenize(char *input)
{
	int		len;

	len = ft_strlen(input);
	if (len == 1 && input[0] && !ft_isalnum(input[0]))
		return (plain_token(input));
	return (compose_token(input));
}

char	*scan_for_errors(t_list *token_list);
int	char_occurences(char *string, int c)
{
	int	occurences;
	int	index;

	index = 0;
	occurences = 0;
	while (string[index])
	{
		if (string[index] == c)
			occurences++;
		index++;
	}
	return (occurences);
}