/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:09:50 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/23 09:43:23 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	int_size(int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (2);
	else if (n < 0)
		i++;
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	char			*dest;
	int				negative;
	unsigned int	size;

	negative = n < 0;
	size = int_size(n);
	dest = malloc(sizeof(char) * (size));
	if (!dest)
		return (NULL);
	dest[--size] = '\0';
	if (!n)
		dest[--size] = '0';
	while (n)
	{
		size--;
		dest[size] = ((-negative + !negative) * (n % 10) + 48);
		n = n / 10;
	}
	if (negative)
		dest[--size] = '-';
	return (dest);
}
