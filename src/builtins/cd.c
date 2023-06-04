/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:57:25 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/04 16:31:47 by lbiasuz          ###   ########.fr       */
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
	char	*owd;
	int		chdir_error;

	if (find_argv_len(argv) > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	path = parse_arguments(find_argv_len(argv), argv);
	owd = getcwd(NULL, 0);
	chdir_error = chdir(path);
	if (path)
		free(path);
	path = getcwd(NULL, 0);
	if (chdir_error)
		perror(argv[1]);
	else
	{
		g_ms.envp = set_value(g_ms.envp, ft_strjoin("OLDPWD=", owd));
		g_ms.envp = set_value(g_ms.envp, ft_strjoin("PWD=", path));
	}
	free(path);
	free(owd);
	return (!(!chdir_error));
}

static char	*parse_arguments(int argc, char *argv[])
{
	char	*final_path;
	char	*pwd;

	final_path = NULL;
	pwd = getcwd(NULL, 0);
	if (argc == 1)
		final_path = get_value(g_ms.envp, "HOME");
	else if (argv[1][0] == '/')
		final_path = ft_strdup(argv[1]);
	else
		final_path = join_three(pwd, "/", argv[1]);
	if (!final_path)
		perror(argv[0]);
	free(pwd);
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
