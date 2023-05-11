/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/11 11:55:12 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms g_ms;

t_cmd	*get_command(t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (!cmd->exe && cmd->raw[i] && !ft_strncmp(cmd->raw[i], PIPE, sizeof(PIPE)))
	{
		if (i == 0 && is_command(cmd->raw[i]))
			cmd->exe = cmd->raw[i];
		i++;
	}
	if (cmd->exe)
		temp = expand_string_content(ft_strdup(cmd->exe));
	if (temp && (!ft_strchr(temp, '/') || temp[0] != '.'))
	{
		cmd->exe_path = find_cmd_path(g_ms.envp, temp);
		free(temp);
	}
	else
		cmd->exe = temp;
	return (cmd);
}

// void	invoke_child(char ***tokens, int fd[2], int ofd[2])
// {
// 	t_cmd	cmd;

// 	redirect_fds(tokens, cmd, fd, ofd);
// 	cmd = get_command(*tokens, cmd);
// 	// cmd = get_args(tokens, cmd);
// 	if (cmd.exe_path)
// 		g_ms.exit_code = execve(cmd.exe_path, cmd.args, g_ms.envp);
// 	exit(g_ms.exit_code);
// }

void	runner(t_list *cmd_list)
{
	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(cast_cmd(cmd_list)->fd);
		run_cmd(cast_cmd(cmd_list), cast_cmd(cmd_list->next));
		close_fd(cast_cmd(cmd_list)->fd[1]);
		close_fd(cast_cmd(cmd_list)->fd[0]);
		cmd_list = cmd_list->next;
	}
}

void	run_cmd(t_cmd *cmd, t_cmd *next)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_fds(cmd, next);
		//cmd = get_command(cmd);
		//cmd = get_args(tokens, cmd);
		if (cmd->exe_path)
			g_ms.exit_code = execve(cmd->exe_path, cmd->args, g_ms.envp);
		exit(g_ms.exit_code);
	}
	close_fd(cmd->fd[0]);
	if (next)
		close_fd(next->fd[1]);
	waitpid(0, &g_ms.exit_code, 0);
	close_fd(cmd->fd[1]);
	if (next)
		close_fd(next->fd[0]);
}