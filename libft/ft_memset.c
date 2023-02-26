/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:18:20 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/16 15:47:09 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, char c, size_t n)
{
	char	*src_aux;

	src_aux = (char *) s;
	if (!n)
		return (NULL);
	while (n--)
		*(src_aux + n) = c;
	*src_aux = c;
	return (s);
}
