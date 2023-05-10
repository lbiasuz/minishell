/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/10 11:15:27 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms g_ms;

int	return_pipe_or_null(char ***parse, int index)
{
	while (*parse[index])
	{
		if (!ft_strncmp((*parse)[index], PIPE, sizeof(PIPE)))
			break ;
		index ++;
	}
	return (index);
}

t_cmd	get_command(char **parse, t_cmd cmd)
{
	char	*command;
	int		i;

	i = 0;
	cmd.exe = NULL;
	command = NULL;
	while (!cmd.exe && parse[i] && !ft_strncmp(parse[i], PIPE, sizeof(PIPE)))
	{
		if (i == 0 && is_command(parse[i]))
			cmd.exe = parse[i];
		i++;
	}
	if (cmd.exe)
		command = expand_string_content(ft_strdup(cmd.exe));
	if (command && (!ft_strchr(command, '/') || command[0] != '.'))
	{
		cmd.exe_path = find_cmd_path(g_ms.envp, command);
		free(command);
	}
	else
		cmd.exe = command;
	return (cmd);
}

void	invoke_child(char ***tokens, int fd[2], int ofd[2])
{
	t_cmd	cmd;

	redirect_fds(tokens, cmd, fd, ofd);
	cmd = get_command(*tokens, cmd);
	// cmd = get_args(tokens, cmd);
	if (cmd.exe_path)
		g_ms.exit_code = execve(cmd.exe_path, cmd.args, g_ms.envp);
	exit(g_ms.exit_code);
}

void	runner(t_list *cmd_list)
{
	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(cast_cmd(cmd_list)->fd);
		// set_pipes(cmd_list);
		run_cmd(cast_cmd(cmd_list));
		close_fd(cast_cmd(cmd_list)->fd[1]);
		close_fd(cast_cmd(cmd_list)->fd[0]);
		cmd_list = cmd_list->next;
	}
}

// void	set_pipes(t_list *cmd_list)
// {

// 	if (!cmd_list->next)
// 		return ;
// 	pipe(cmd_list->next->cmd.fd);
// }

void	run_cmd(t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_fds(cmd);
		cmd = get_command(cmd);
	// 	cmd = get_args(tokens, cmd);
		if (cmd.exe_path)
			g_ms.exit_code = execve(cmd->exe_path, cmd->args, g_ms.envp);
		exit(g_ms.exit_code);
	}
	if (fd[1] >= 3)
		close(fd[1]);
	if (ofd[0] >= 3)
		close(ofd[0]);
	waitpid(0, &g_ms.exit_code, 0);
	if (fd[0] >= 3)
		close(fd[0]);
	if (ofd[1] >= 3)
		close(ofd[1]);
}