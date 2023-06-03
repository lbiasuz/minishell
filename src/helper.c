/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:21:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/03 10:21:04 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <libft.h>

extern t_ms	g_ms;

t_cmd	*cast_cmd(t_list *node)
{
	if (node && node->content)
		return ((t_cmd *) node->content);
	return (NULL);
}

void	close_fd(int fd)
{
	if (fd >= 3)
		close(fd);
}

void	free_node(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (cmd->exe)
		free(cmd->exe);
	if (cmd->exe_path)
		free(cmd->exe_path);
	if (cmd->args)
	{
		free_table(cmd->args);
		free(cmd->args);
	}
	if (cmd->raw)
	{
		free_table(cmd->raw);
		free(cmd->raw);
	}
	free(cmd);
}

void	func_heredoc_handler(int signo)
{
	(void)signo;
	g_ms.exit_code = 130;
	write(2, "\n", 1);
	exit(130);
}

void	set_heredoc_signal_handlers(void)
{
	t_sigaction			act;
	static t_sigaction	old_act;
	static int			restore_flag;

	if (restore_flag++)
	{
		sigaction(SIGINT, &old_act, NULL);
		restore_flag--;
		return ;
	}
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = &func_heredoc_handler;
	sigaction(SIGINT, &act, &old_act);
}
