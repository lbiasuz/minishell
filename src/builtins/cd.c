/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:57:25 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/14 01:06:50 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h> // perror
#include <stdlib.h> // getenv
#include <unistd.h> // chdir

static char	*parse_arguments(int argc, char *argv[]);
static int	find_argv_len(char **argv);

int	cd(char *argv[])
{
	char	*path;
	int		chdir_error;
	int		argc;

	argc = find_argv_len(argv);
	path = parse_arguments(argc, argv);
	chdir_error = chdir(path);
	if (path)
		free(path);
	if (chdir_error)
		perror("chdir() by cd.a");
	return (chdir_error);
}

static char	*parse_arguments(int argc, char *argv[])
{
	char	*final_path;

	final_path = NULL;
	if (argc == 1)
		final_path = ft_strdup(getenv("USER_ZDOTDIR"));
	else
		final_path = ft_strjoin(getenv("PWD"), argv[1]);
	if (!final_path)
	{
		perror("allocation by parse_arguments by cd.a");
		exit(-1);
	}
	return (final_path);
}

static int	find_argv_len(char **argv)
{
	int	counter;

	counter = 0;
	while (argv[0])
	{
		argv++;
		counter++;
	}
	return (counter);
}
