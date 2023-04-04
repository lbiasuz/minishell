/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:03:16 by rmiranda          #+#    #+#             */
/*   Updated: 2023/04/04 20:05:46 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h> // perror
#include <stdlib.h> // getenv

int	pwd(void)
{
	char	*pwd_pathname;

	pwd_pathname = getenv("PWD");
	if (!pwd_pathname)
	{
		perror("getenv() by pwd.a");
		return (-1);
	}
	ft_putendl_fd(pwd_pathname, 1);
	return (0);
}
