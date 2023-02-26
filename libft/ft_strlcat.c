/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:49:52 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/23 09:42:30 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	offset_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	offset_len = dest_len;
	if (size == 0)
		return (src_len);
	else if (size < dest_len)
		return (size + src_len);
	while (*src != '\0' && offset_len < size - 1)
	{
		*(dest + offset_len) = *src;
		src++;
		offset_len++;
	}
	*(dest + offset_len) = '\0';
	return (dest_len + src_len);
}
