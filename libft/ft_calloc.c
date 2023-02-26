/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:47:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/30 03:07:22 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*dest;
	int				check;
	unsigned int	i;

	i = 0;
	check = nmemb > size;
	if ((nmemb * size) < ((nmemb * check) + (size * !check)))
		return (NULL);
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	while (i < (nmemb * size))
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
