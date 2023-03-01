/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:03:16 by rmiranda          #+#    #+#             */
/*   Updated: 2023/02/28 21:52:36 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h> // perror
#include <stdlib.h> // getenv

int	main(void)
{
	char	*pwd_pathname;

	pwd_pathname = getenv("PWD");
	if (!pwd_pathname)
	{
		perror("getenv(pwd) by pwd.a");
		return (-1);
	}
	ft_putendl_fd(pwd_pathname, 1);
	return (0);
}
