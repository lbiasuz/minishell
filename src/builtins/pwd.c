/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:03:16 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/22 22:22:13 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

int	pwd(void)
{
	char	*pwd_pathname;

	pwd_pathname = get_value(g_ms.envp, "PWD");
	if (!pwd_pathname)
	{
		perror("getenv() by pwd.a");
		return (-1);
	}
	ft_putendl_fd(pwd_pathname, 1);
	free(pwd_pathname);
	return (0);
}
