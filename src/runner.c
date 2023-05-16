/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/16 12:03:34 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms g_ms;

void	build_command(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->exe = NULL;
	while (cmd->raw[i] && ft_strncmp(cmd->raw[i], PIPE, sizeof(PIPE)))
	{
		if (is_redirect(cmd->raw[i]))
			i++;
		else if (!is_token(cmd->raw[i]) && !cmd->exe)
		{
			cmd->exe = exp_str_content(ft_strdup(cmd->raw[i]));
			cmd->args = append_table(NULL, ft_strdup(cmd->exe));
		}
		else if (!is_token(cmd->raw[i]))
			cmd->args = append_table(cmd->args, exp_str_content(cmd->raw[i]));
		i++;
	}
	if (cmd->exe && (!ft_strchr(cmd->exe, '/') && cmd->exe[0] != '.'))
		cmd->exe_path = find_cmd_path(g_ms.envp, cmd->exe);
	else if (access(cmd->exe, X_OK) != -1)
		cmd->exe_path = cmd->exe;
	else
		cmd->exe_path = NULL;
}

static int	exec_builtin(t_cmd *cmd)
{
	build_command(cmd);
	if (!ft_strncmp(cmd->args[0], "cd", sizeof("cd")))
		return (cd(cmd->args));
	if (!ft_strncmp(cmd->args[0], "echo", sizeof("echo")))
		return (echo(cmd->args));
	if (!ft_strncmp(cmd->args[0], "env", sizeof("env")))
		return (env());
	if (!ft_strncmp(cmd->args[0], "export", sizeof("export")))
		return (export(cmd->args));
	if (!ft_strncmp(cmd->args[0], "pwd", sizeof("pwd")))
		return (pwd());
	if (!ft_strncmp(cmd->args[0], "unset", sizeof("unset")))
		return (unset(cmd->args));
	return (-1);
}

static int	byp_builtin(char *cmd_str)
{
	if (!ft_strncmp(cmd_str, "cd", sizeof("cd"))
		|| !ft_strncmp(cmd_str, "echo", sizeof("echo"))
		|| !ft_strncmp(cmd_str, "env", sizeof("env"))
		|| !ft_strncmp(cmd_str, "export", sizeof("export"))
		|| !ft_strncmp(cmd_str, "pwd", sizeof("pwd"))
		|| !ft_strncmp(cmd_str, "unset", sizeof("unset")))
		return (1);
	return (0);
}

static char *get_exe(char **table)
{
	int i;

	i = 0;
	while (table[i] && ft_strncmp(table[i], PIPE, sizeof(PIPE)))
	{
		if (is_redirect(table[i]))
			i++;
		else if (!is_token(table[i]))
			return (table[i]);
		i++;
	}
	return (table[i]);
}

void	runner(t_list *cmd_list)
{
	t_list	*aux;

	aux = cmd_list;
	if (!aux->next && byp_builtin(get_exe(cast_cmd(aux)->raw)))
	{
		redirect_fds(cast_cmd(aux), cast_cmd(aux->next));
		exec_builtin(cast_cmd(aux));
	}
	else
	{
		while (cmd_list)
		{
			if (cmd_list->next)
				pipe(cast_cmd(cmd_list->next)->fd);
			else
				run_cmd(cast_cmd(cmd_list), cast_cmd(cmd_list->next));
			close_fd(cast_cmd(cmd_list)->fd[1]);
			close_fd(cast_cmd(cmd_list)->fd[0]);
			cmd_list = cmd_list->next;
		}
		while (aux)
		{
			waitpid(0, &g_ms.exit_code, 0);
			aux = aux->next;
		}
	}
}

void	run_cmd(t_cmd *cmd, t_cmd *next)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_fds(cmd, next);
		build_command(cmd);
		if (byp_builtin(cmd->exe))
		{
			g_ms.exit_code = exec_builtin(cmd);
			exit(0);
		}
		else if (cmd->exe_path)
			g_ms.exit_code = execve(cmd->exe_path, cmd->args, g_ms.envp);
	}
}
