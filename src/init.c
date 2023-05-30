/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:57:05 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/29 23:24:22 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
extern t_ms	g_ms;

t_ms	init_minishell(char **env)
{
	t_ms	ms;

	ms.pid = 1;
	init_signal_handlers(1);
	ms.envp = copy_environment(env);
	ms.exit_code = 0;
	ms.commands = NULL;
	return (ms);
}

static void	func_sig_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	init_signal_handlers(int flag)
{
	t_sigaction	act_int;
	t_sigaction	act_quit;
	static t_sigaction	act_int_old;
	static t_sigaction	act_quit_old;

	if (!flag)
	{
		sigaction(SIGINT, &act_int_old, NULL);
		sigaction(SIGQUIT, &act_quit_old, NULL);
		return ;
	}
	sigemptyset(&act_int.sa_mask);
	sigemptyset(&act_quit.sa_mask);
	act_int.sa_flags = SA_RESTART;
	act_int.sa_handler = &func_sig_handler;
	sigaction(SIGINT, &act_int, &act_int_old);
	act_quit.sa_flags = 0;
	act_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act_quit, &act_quit_old);
}

