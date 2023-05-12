/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/12 11:53:22 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms g_ms;

void	get_command(t_cmd *cmd)
{
	int		i;

	i = 0;
	cmd->exe = NULL;
	while (cmd->raw[i] && ft_strncmp(cmd->raw[i], PIPE, sizeof(PIPE)))
	{
		if (is_redirect(cmd->raw[i]))
			i++;
		else if (!is_token(cmd->raw[i]) && !cmd->exe)
		{
			cmd->exe = expand_string_content(ft_strdup(cmd->raw[i]));
			cmd->args = append_table(NULL, ft_strdup(cmd->exe));
		}
		else if (!is_token(cmd->raw[i]))
			cmd->args = append_table(cmd->args, expand_string_content(cmd->raw[i]));
		i++;
	}
	if (cmd->exe && (!ft_strchr(cmd->exe, '/') || cmd->exe[0] != '.'))
		cmd->exe_path = find_cmd_path(g_ms.envp, cmd->exe);
}

void	runner(t_list *cmd_list)
{
	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(cast_cmd(cmd_list->next)->fd);
		run_cmd(cast_cmd(cmd_list), cast_cmd(cmd_list->next));
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
		get_command(cmd);
		if (cmd->exe_path)
			g_ms.exit_code = execve(cmd->exe_path, cmd->args, g_ms.envp);
		exit(g_ms.exit_code);
	}
	if (next)
		close_fd(next->fd[1]);
	close_fd(cmd->fd[0]);
	waitpid(0, &g_ms.exit_code, 0);
	if (next)
		close_fd(next->fd[0]);
	close_fd(cmd->fd[1]);
}