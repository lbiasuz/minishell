/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:00:36 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/18 21:34:26 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

int	expand_dollar_sign(char *input, char *dollar)
{
	char	**occurences;
	int		flag;
	int		index;

	occurences = char_occurences(input, '\'');
	index = 0;
	while (occurences[index] && occurences[index] < dollar)
		index++;
	if (occurences[index] && index % 2 == 0)
		flag = 1;
	else
		flag = 0;
	free(occurences);
	return (flag);
}

char	*join_envp_var(char *before, char *variable, char *after)
{
	char	*join1;
	char	*join2;
	
	if (!before)
		before = "";
	if (!variable)
		variable = "";
	if (!after)
		after = "";
	join1 = ft_strjoin(before, variable);
	join2 = ft_strjoin(join1, after);
	free(join1);
	return (join2);
}

char	*expand_variable(char *input, char *dollar)
{
	int		index;
	char	*variable;
	char	*value;

	index = 1;
	if (!dollar)
		return (input);
	while (ft_isalnum(dollar[index]) || dollar[index] == '_')
		index++;
	variable = ft_substr(dollar, 1, index);
	value = get_value(g_ms.envp, variable);
	return (join_envp_var(
			ft_substr(input, 0, dollar - input),
			value,
			ft_substr(&input[index - 1], 0, ft_strlen(&input[index]))
		)
	);
}

void	expand_token_content(t_list *node)
{
	while (gvle(node))
	{
		if (!ft_strchr(gvle(node), '$'))
			break ;
		((t_tkn *) node->content)->value = expand_variable(
				gvle(node),
				ft_strchr(gvle(node), '$')
				);
	}
}
