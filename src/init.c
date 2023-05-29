/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 09:57:05 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/29 15:58:31 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	init_signal_handlers(void);

t_ms	init_minishell(char **env)
{
	t_ms	ms;

	init_signal_handlers();
	ms.envp = copy_environment(env);
	ms.exit_code = 0;
	ms.commands = NULL;
	return (ms);
}

static void	func_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

static void	init_signal_handlers(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = func_sig_handler;
	sigaction(SIGINT, &act, (struct sigaction *) NULL);
	sigaction(SIGQUIT, &act, (struct sigaction *) NULL);
}
