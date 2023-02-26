/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 20:01:05 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/23 09:06:21 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	i;
	char			*d;

	i = ft_strlen(s) + 1;
	d = (char *) ft_calloc(i, sizeof(char));
	if (!d)
		return (NULL);
	ft_strlcpy(d, s, i);
	if (ft_strlen(d) != i -1)
		return (NULL);
	return (d);
}
