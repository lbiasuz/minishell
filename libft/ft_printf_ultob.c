/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_converters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:18:27 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/01/31 09:54:42 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*ft_ultob(unsigned long long nb, char *base)
{
	char	*output;
	int		base_len;
	int		size;

	if (!nb)
		return (ft_strdup("(nil)"));
	base_len = ft_strlen(base);
	size = long_long_size(nb, base_len);
	output = (char *) malloc(sizeof(char) * (size + 2));
	size = size + 2;
	if (!output)
		return (NULL);
	output[--size] = '\0';
	while (size && nb)
	{
		output[--size] = base[nb % base_len];
		nb = nb / base_len;
	}
	output[--size] = 'x';
	output[--size] = '0';
	return (output);
}
