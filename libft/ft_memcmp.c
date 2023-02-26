/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:37:57 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/25 23:13:53 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*aux1;
	unsigned char	*aux2;
	unsigned int	i;

	i = 0;
	aux1 = (unsigned char *) s1;
	aux2 = (unsigned char *) s2;
	if (!n)
		return (0);
	while (i < n - 1 && aux1[i] == aux2[i])
		i++;
	return (aux1[i] - aux2[i]);
}
