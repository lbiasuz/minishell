/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:57:25 by rmiranda          #+#    #+#             */
/*   Updated: 2023/03/01 20:36:48 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h> // perror
#include <stdlib.h> // getenv
#include <unistd.h> // chdir

static char	*parse_arguments(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	char	*path;
	int		chdir_error;

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
