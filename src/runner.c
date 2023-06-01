/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/01 11:37:24 by rmiranda         ###   ########.fr       */
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

void	exec_sinle_builtin(t_cmd *cmd)
{
	int	dupped_fd_in;
	int	dupped_fd_out;

	dupped_fd_in = dup(STDIN_FILENO);
	dupped_fd_out = dup(STDOUT_FILENO);
	redirect_fds(cmd);
	g_ms.exit_code = exec_builtin(cmd);
	dup2(dupped_fd_in, STDIN_FILENO);
	dup2(dupped_fd_out, STDOUT_FILENO);
	close(dupped_fd_in);
	close(dupped_fd_out);
}

static int	get_pipe(t_list *cmd_list)
{
	int	*here_fd;
	int	*next_fd;
	int	pipe_result[2];

	here_fd = cast_cmd(cmd_list)->fd;
	next_fd = cast_cmd(cmd_list->next)->fd;
	if (pipe(pipe_result))
	{
		perror("get_pipe: pipe");
		return (-1);
	}
	here_fd[1] = pipe_result[1];
	next_fd[0] = pipe_result[0];
	return (0);
}

void	runner(t_list *cmd_list)
{
	t_list	*aux;

	aux = cmd_list;
	if (!aux->next && is_builtin(cast_cmd(aux)->exe))
		exec_sinle_builtin(cast_cmd(aux));
	else
	{
		while (cmd_list)
		{
			if (cmd_list->next)
				get_pipe(cmd_list);
			run_cmd(cast_cmd(cmd_list));
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

void	run_cmd(t_cmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		init_signal_handlers(0);
		redirect_fds(cmd);
		if (!cmd->exe)
			;
		else if (is_builtin(cmd->exe))
			g_ms.exit_code = exec_builtin(cmd);
		else if (cmd->exe_path)
			g_ms.exit_code = execve(cmd->exe_path, cmd->args, g_ms.envp);
		else
		{
			write(2, cmd->exe, ft_strlen(cmd->exe));
			write(2, ERROR_CNF, ft_strlen(ERROR_CNF));
			exit(512);
		}
		exit(0);
	}
}
