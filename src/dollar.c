/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:00:36 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/18 18:34:05 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

static char	*join_envp_var_dol(char *before, char *variable, char *after)
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
	free(before);
	free(after);
	return (join2);
}

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

char	*expand_variable(char *input, char *dollar)
{
	int		index;
	char	*variable;
	char	*value;

	index = 1;
	if (!dollar)
		return (input);
	if (dollar[index] == '?')
		return (join_envp_var_dol(
				ft_substr(input, 0, dollar - input),
				ft_itoa(g_ms.exit_code),
				ft_substr(&dollar[2], 0, ft_strlen(&input[index]))
			));
	while (ft_isalnum(dollar[index]) || dollar[index] == '_')
		index++;
	variable = ft_substr(dollar, 1, index);
	value = get_value(g_ms.envp, variable);
	free(variable);
	variable = join_envp_var_dol(
			ft_substr(input, 0, dollar - input),
			value, ft_substr(&input[index - 1], 0, ft_strlen(&input[index])));
	free(value);
	return (variable);
}

char	*exp_str_content(char *string)
{
	char	*new_string;

	while (ft_strchr(string, '$'))
	{
		new_string = expand_variable(string, ft_strchr(string, '$'));
		if (new_string != string)
		{
			free(string);
			string = new_string;
		}
	}
	return (string);
}
