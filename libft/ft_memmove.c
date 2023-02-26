/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:14:19 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/16 15:28:50 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*d;
	char			*s;

	d = (char *) dest;
	s = (char *) src;
	if (d > s)
		while (n--)
			*(d + n) = *(s + n);
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
