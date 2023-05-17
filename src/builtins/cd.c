/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:57:25 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/16 21:27:41 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h> // perror
#include <stdlib.h> // getenv
#include <unistd.h> // chdir

extern t_ms	g_ms;

static char	*parse_arguments(int argc, char *argv[]);
static int	find_argv_len(char **argv);

static char	*join_three(char *before, char *variable, char *after)
{
	char	*join1;
	char	*join2;

	if (!before)
		before = "";
	if (!variable)
		variable = "";
	if (!after)
		after = "";
	join1 = ft_strjoin(before, variable);
	join2 = ft_strjoin(join1, after);
	free(join1);
	return (join2);
}

int	cd(char *argv[])
{
	char	*path;
	int		chdir_error;
	int		argc;

	argc = find_argv_len(argv);
	path = parse_arguments(argc, argv);
	chdir_error = chdir(path);
	set_value(g_ms.envp, ft_strjoin("PWD=", path));
	if (path)
		free(path);
	if (chdir_error)
		perror(path);
	return (chdir_error);
}

static char	*parse_arguments(int argc, char *argv[])
{
	char	*final_path;

	final_path = NULL;
	if (argc == 1)
		final_path = ft_strdup(get_value(g_ms.envp, "USER_ZDOTDIR"));
	else if (!get_value(g_ms.envp, "PWD")[ft_strlen(get_value(g_ms.envp, "PWD"))])
		final_path = join_three(get_value(g_ms.envp, "PWD"), "/", argv[1]);
	else
		final_path = ft_strjoin(get_value(g_ms.envp, "PWD"), argv[1]);
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
