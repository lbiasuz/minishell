/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/17 19:36:58 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

static int	exec_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "cd", sizeof("cd")))
		return (cd(cmd->args));
	if (!ft_strncmp(cmd->args[0], "echo", sizeof("echo")))
		return (echo(cmd->args));
	if (!ft_strncmp(cmd->args[0], "env", sizeof("env")))
		return (env());
	if (!ft_strncmp(cmd->args[0], "exit", sizeof("exit")))
		return (ms_exit(cmd->args));
	if (!ft_strncmp(cmd->args[0], "export", sizeof("export")))
		return (export(cmd->args));
	if (!ft_strncmp(cmd->args[0], "pwd", sizeof("pwd")))
		return (pwd());
	if (!ft_strncmp(cmd->args[0], "unset", sizeof("unset")))
		return (unset(cmd->args));
	return (-1);
}

static char	*get_exe(char **table)
{
	int	i;

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
		if (byp_builtin(cmd->exe))
		{
			g_ms.exit_code = exec_builtin(cmd);
			exit(0);
		}
		else if (cmd->exe_path)
			g_ms.exit_code = execve(cmd->exe_path, cmd->args, g_ms.envp);
	}
}
