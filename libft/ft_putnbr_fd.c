/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:08:35 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/26 13:05:42 by lbiasuz          ###   ########.fr       */
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
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	char			str[12];
	int				neg;
	unsigned int	i;

	neg = n < 0;
	ft_bzero(str, 12);
	i = int_size(n) - 1;
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[i] = ((-(neg) + !neg) * (n % 10)) + 48;
		n = n / 10;
		i--;
	}
	if (neg)
		str[i] = '-';
	write(fd, str, ft_strlen(str));
}
