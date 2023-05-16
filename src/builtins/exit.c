/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 10:22:24 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/16 11:17:26 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_value_from_table(char **input);
static int	count_table(char **input);

int	ms_exit(char **argv)
{
	int	arguments_count;
	int	exit_value;

	arguments_count = count_table(argv);
	if (arguments_count > 2)
	{
		errno = E2BIG;
		perror("minishell ms_exit.c:27");
		return (0);
	}
	exit_value = get_value_from_table(argv);
	write(1, "exit ", 5);
	ft_putnbr_fd(exit_value, 1);
	write(1, "\n", 1);
	exit(exit_value);
}

static int	count_table(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

static int	get_value_from_table(char **argv)
{
	int	value;


	if (!argv[1])
		value = 0;
	else
		value = ft_atoi(argv[1]);
	return (value);
}
