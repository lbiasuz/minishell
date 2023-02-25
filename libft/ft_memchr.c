/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 20:49:13 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/12 23:22:41 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*aux;

	aux = (char *) s;
	while (n)
	{
		if (*aux == (char) c)
			return (aux);
		aux++;
		n--;
	}
	return (NULL);
}
