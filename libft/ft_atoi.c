/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:15:38 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/02/28 11:18:35 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		n = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		i = (i * 10) + (*nptr - 48);
		nptr++;
	}
	return (i * n);
}
