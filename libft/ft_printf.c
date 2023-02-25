/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:56:33 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/07/09 23:14:12 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		printed;
	va_list	args;

	va_start(args, str);
	printed = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			printed += handle_print_conversion(args, *str);
			str++;
		}
		else
		{
			ft_putchar_fd(*str, 1);
			printed++;
			str++;
		}
	}
	va_end(args);
	return (printed);
}

int	handle_print_conversion(va_list args, int cflag)
{
	char	*value;
	int		len;

	value = NULL;
	if (cflag == 'd' || cflag == 'i')
		value = ft_itoa(va_arg(args, int));
	else if (cflag == 'u')
		value = ft_utoa(va_arg(args, unsigned int));
	else if (cflag == 'x')
		value = ft_itob(va_arg(args, unsigned int), "0123456789abcdef");
	else if (cflag == 'X')
		value = ft_itob(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (cflag == 'p')
		value = ft_ultob(va_arg(args, unsigned long long), "0123456789abcdef");
	else if (cflag == 's' || cflag == 'c')
		value = alloc_char_or_string(args, cflag);
	else
		value = ft_strdup("%");
	len = (1 * cflag == 'c' && *value == 0) + ft_strlen(value);
	ft_putstr_fd(value, 1);
	if (1 * cflag == 'c' && *value == 0)
		ft_putchar_fd(*value, 1);
	if (value != NULL && ft_strchr("csdiuxXp%", cflag))
		free(value);
	return (len);
}

char	*alloc_char_or_string(va_list list, int type_flag)
{
	char	*value;

	value = NULL;
	if (type_flag == 'c')
	{
		value = malloc(sizeof(char) * 2);
		if (!value)
			return (NULL);
		value[0] = va_arg(list, int);
		value[1] = 0;
	}
	else if (type_flag == 's')
	{
		value = va_arg(list, char *);
		if (!value)
			value = ft_strdup("(null)");
		else
			value = ft_strdup(value);
	}
	return (value);
}
