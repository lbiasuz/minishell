/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:13:23 by rmiranda          #+#    #+#             */
/*   Updated: 2023/03/16 23:30:05 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h" // striteri putstr_fd putchar_fd
#include <stdlib.h> // exit

static void	parse_arguments(int arg_c, char *argv[]);
static void	func_is_valid_char(unsigned int index, char *str);
static void	output(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	parse_arguments(argc, argv);
	output(argc, argv);
	return (0);
}

static void	parse_arguments(int argc, char *argv[])
{
	int	argc_counter;

	argc_counter = 1;
	while (argc_counter < argc)
		ft_striteri(argv[argc_counter++], &func_is_valid_char);
}

void	func_is_valid_char(unsigned int index, char *str)
{
	if (!ft_isascii(str[index]))
	{
		ft_putstr_fd("Error: NOT ASCII", 2);
		exit(-1);
	}
}

static void	output(int argc, char *argv[])
{
	int		argc_counter;
	int		nl_flag;

	argc_counter = 1;
	nl_flag = 0;
	if (argc > 1)
	{
		if (!ft_strncmp("-n", argv[argc_counter], 2) && ++nl_flag)
		{
			if (ft_strlen(argv[argc_counter]) > 2)
				argv[argc_counter] += 3;
			else
				argc_counter++;
		}
		while (argc_counter < argc)
		{
			if (argc_counter > 1 + nl_flag)
				ft_putchar_fd(' ', 1);
			ft_putstr_fd(argv[argc_counter], 1);
			argc_counter++;
		}
	}
	if (!nl_flag)
		ft_putchar_fd('\n', 1);
}
