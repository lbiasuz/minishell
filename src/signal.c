/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:21:15 by rmiranda          #+#    #+#             */
/*   Updated: 2023/04/05 18:56:35 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	func_sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	init_signal_handlers(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = func_sig_handler;
	sigaction(SIGINT, &act, (struct sigaction *) NULL);
	sigaction(SIGQUIT, &act, (struct sigaction *) NULL);
}
