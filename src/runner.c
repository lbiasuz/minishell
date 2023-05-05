/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/05 08:57:35 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms g_ms;

char	**return_pipe_or_null(char **parse, int index)
{
	while (parse[index])
	{
		if (!ft_strncmp(parse[index], PIPE, sizeof(PIPE)))
			break ;
		index ++;
	}
	return (&parse[index]);
}

t_cmd	get_command(char **parse, t_cmd cmd)
{
	char	*command;
	int		i;

	i = 0;
	cmd.exe = NULL;
	while (!cmd.exe && parse[i] && !ft_strncmp(parse[i], PIPE, sizeof(PIPE)))
	{
		if (is_command(parse[i], parse[i - 1]))
			cmd.exe = parse[i]
		i++;
	}
	command = expand_token_content(cmd.exe);
	if (command && (!ft_strchr(command, '/') || command[0] != '.'))
	{
		cmd.exe_path = find_cmd_path(g_ms.envp, command);
		free(command);
	}
	else
		cmd.exe = command;
	return (cmd);
}

void	invoke_child(t_list *tokens, int fd[2], int ofd[2])
{
	t_cmd	cmd;

	cmd = redirect_fds(tokens, cmd, fd, ofd);
	cmd = get_command(tokens, cmd);
	cmd = get_args(tokens, cmd);
	if (cmd.exe_path)
		g_ms.exit_code = execve(cmd.exe_path, cmd.args, g_ms.envp);
	exit(g_ms.exit_code);
}

void	runner(char **parsed, int pid, int fd[2], int ofd[2])
{

	node = return_pipe_or_null(token);
	if (node)
	{
		ofd[0] = fd[0];
		ofd[1] = fd[1];
		pipe(fd);
	}
	pid = fork();
	if (pid == 0)
		invoke_child(token, fd, ofd);
	if (fd[1] >= 3)
		close(fd[1]);
	if (ofd[0] >= 3)
		close(ofd[0]);
	if (node && pid != 0)
		runner(node->next, pid, fd, ofd);
	waitpid(0, &g_ms.exit_code, 0);
	if (fd[0] >= 3)
		close(fd[0]);
	if (ofd[1] >= 3)
		close(ofd[1]);
}
