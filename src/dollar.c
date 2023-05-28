/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 22:00:36 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/27 11:11:45 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

char	*join_var(char *before, char *variable, char *after)
{
	char	*join1;
	char	*join2;

	if (!before)
		before = ft_strdup("");
	if (!variable)
		variable = ft_strdup("");
	if (!after)
		after = ft_strdup("");
	join1 = ft_strjoin(before, variable);
	join2 = ft_strjoin(join1, after);
	free(join1);
	free(before);
	free(after);
	free(variable);
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
	if (dollar[index] == '?' && index++)
		value = ft_itoa(g_ms.exit_code);
	else
	{
		while (ft_isalnum(dollar[index]) || dollar[index] == '_')
			index++;
		variable = ft_substr(dollar, 1, index - 1);
		value = get_value(g_ms.envp, variable);
		free(variable);
	}
	return join_var(
		ft_substr(input, 0, dollar - input),
		value, ft_substr(&dollar[index], 0, ft_strlen(&dollar[index])));
}

char	*replace_env_variables(char *string)
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
