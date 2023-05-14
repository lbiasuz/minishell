/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/14 02:33:09 by rmiranda         ###   ########.fr       */
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

static int	exec_builtin(char	**cmd_str_table)
{
	if (!ft_strncmp(cmd_str_table[0], "cd", sizeof("cd")))
		return (cd(cmd_str_table));
	if (!ft_strncmp(cmd_str_table[0], "echo", sizeof("echo")))
		return (echo(cmd_str_table));
	if (!ft_strncmp(cmd_str_table[0], "env", sizeof("env")))
		return (env());
	if (!ft_strncmp(cmd_str_table[0], "export", sizeof("export")))
		return (export(cmd_str_table));
	if (!ft_strncmp(cmd_str_table[0], "pwd", sizeof("pwd")))
		return (pwd());
	if (!ft_strncmp(cmd_str_table[0], "unset", sizeof("unset")))
		return (unset(cmd_str_table));
	return (-1);
}

static int		byp_builtin(char **cmd_str_table)
{
	int		is_builtin;

	is_builtin = 0;
	if (!ft_strncmp(cmd_str_table[0], "cd", sizeof("cd"))
		|| !ft_strncmp(cmd_str_table[0], "echo", sizeof("echo"))
		|| !ft_strncmp(cmd_str_table[0], "env", sizeof("env"))
		|| !ft_strncmp(cmd_str_table[0], "export", sizeof("export"))
		|| !ft_strncmp(cmd_str_table[0], "pwd", sizeof("pwd"))
		|| !ft_strncmp(cmd_str_table[0], "unset", sizeof("unset")))
		is_builtin++;
	return (is_builtin);
}

void	runner(t_list *cmd_list)
{
	while (cmd_list)
	{
		if (cmd_list->next)
			pipe(cast_cmd(cmd_list->next)->fd);
		if (!cmd_list->next && byp_builtin(cast_cmd(cmd_list)->raw))
			g_ms.exit_code = exec_builtin(cast_cmd(cmd_list)->raw);
		else
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
		if (byp_builtin(cmd->raw))
		{
			ft_printf("HERE"); 
			exit(exec_builtin(cmd->raw));
		}
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