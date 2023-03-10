/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:15:15 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/01/31 09:46:23 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

long	ft_absl(long n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}
