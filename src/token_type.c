/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 20:18:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/19 10:20:30 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_redirect(char *token)
{
	if (!token)
		return (0);
	return (!ft_strncmp(token, DCHEV, sizeof(DCHEV))
		|| !ft_strncmp(token, CHEV, sizeof(CHEV))
		|| !ft_strncmp(token, ICHEV, sizeof(ICHEV)));
}

int	is_token(char *string)
{
	return (!ft_strncmp(string, DICHEV, sizeof(DICHEV))
		|| !ft_strncmp(string, DCHEV, sizeof(DCHEV))
		|| !ft_strncmp(string, CHEV, sizeof(CHEV))
		|| !ft_strncmp(string, ICHEV, sizeof(ICHEV))
		|| !ft_strncmp(string, PIPE, sizeof(PIPE))
		|| !ft_strncmp(string, ECOM, sizeof(ECOM)));
}

int	is_command(char	*token)
{
	if (!token)
		return (0);
	return (!is_token(token)
		&& (!ft_strncmp(token, EXPAND, sizeof(EXPAND))
			|| !ft_strncmp(token, TEXT, sizeof(TEXT))
			|| !ft_strncmp(token, SQUOTE, sizeof(SQUOTE))
			|| !ft_strncmp(token, DQUOTE, sizeof(DQUOTE)))
	);
}

int	is_builtin(char *cmd_str)
{
	if (!ft_strncmp(cmd_str, "cd", sizeof("cd"))
		|| !ft_strncmp(cmd_str, "echo", sizeof("echo"))
		|| !ft_strncmp(cmd_str, "env", sizeof("env"))
		|| !ft_strncmp(cmd_str, "exit", sizeof("exit"))
		|| !ft_strncmp(cmd_str, "export", sizeof("export"))
		|| !ft_strncmp(cmd_str, "pwd", sizeof("pwd"))
		|| !ft_strncmp(cmd_str, "unset", sizeof("unset")))
		return (1);
	return (0);
}
