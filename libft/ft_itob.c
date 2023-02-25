/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:51:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/01/31 09:52:39 by lbiasuz          ###   ########.fr       */
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

char	*ft_itob(unsigned int nb, char *base)
{
	char	*output;
	int		base_len;
	int		size;

	base_len = ft_strlen(base);
	size = long_long_size(nb, base_len);
	output = (char *) malloc(sizeof(char) * (size));
	if (!output)
		return (NULL);
	output[--size] = '\0';
	if (!nb)
		output[--size] = '0';
	while (nb)
	{
		output[--size] = base[nb % base_len];
		nb = nb / base_len;
	}
	return (output);
}
