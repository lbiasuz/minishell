/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:53:33 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/01/31 09:54:02 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	long_long_size(unsigned long long nb, int base_len)
{
	unsigned int	i;

	i = 1;
	if (nb <= 0)
		i++;
	while (nb)
	{
		i++;
		nb = nb / base_len;
	}
	return (i);
}

char	*ft_utoa(unsigned int nb)
{
	char	*output;
	int		size;

	size = long_long_size(nb, 10);
	output = (char *) malloc(sizeof(char) * (size + 1));
	if (!output)
		return (NULL);
	output[--size] = '\0';
	if (!nb)
		output[--size] = '0';
	while (nb)
	{
		output[--size] = ((nb % 10) + 48);
		nb = nb / 10;
	}
	return (output);
}
