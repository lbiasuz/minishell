/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:57:05 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/03 18:44:51 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms	g_ms;

t_ms	init_minishell(char **env)
{
	t_ms	ms;

	set_init_signal_handlers(1);
	ms.envp = copy_environment(env);
	ms.exit_code = 0;
	ms.exit_code_previous = 0;
	ms.commands = NULL;
	return (ms);
}

static void	func_sig_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	rl_replace_line("", 1);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	set_init_signal_handlers(int pid)
{
	t_sigaction			act_int;
	t_sigaction			act_quit;

	(void)pid;
	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_quit.sa_mask);
	act_int.sa_flags = SA_RESTART;
	act_int.sa_handler = &func_sig_handler;
	sigaction(SIGINT, &act_int, NULL);
	act_quit.sa_flags = 0;
	act_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act_quit, NULL);
}

static void	func_child_sig_handler(int signo)
{
	(void)signo;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
}

void	set_exec_signal_handlers(int pid)
{
	t_sigaction			act_quit;

	sigemptyset(&act_quit.sa_mask);
	act_quit.sa_flags = 0;
	if (pid == 0)
		act_quit.sa_handler = &func_child_sig_handler;
	else
		act_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act_quit, NULL);
	sigaction(SIGINT, &act_quit, NULL);
}
