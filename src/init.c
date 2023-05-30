/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:57:05 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/29 23:30:12 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

void	set_signal(int sig, void (*handler)(int), int flags)
{
	t_sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = flags;
	act.sa_handler = handler;
	sigaction(sig, &act, NULL);
}

void	child_sig(int signal_number)
{
	(void)signal_number;
	ft_putendl_fd("", STDERR_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
}

void	prompt_handle(int signal_number)
{
	(void)signal_number;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	prompt_signals(void)
{
	set_signal(SIGINT, &prompt_handle, SA_RESTART);
	set_signal(SIGQUIT, SIG_IGN, 0);
}

t_ms	init_minishell(char **env)
{
	t_ms	ms;

	ms.envp = copy_environment(env);
	ms.exit_code = 0;
	ms.commands = NULL;
	ms.pid = 1;
	return (ms);
}
