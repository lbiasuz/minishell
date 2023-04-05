/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:12:35 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/05 18:53:17 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <ft_printf.h>

// READLINE FUNCTION HEADERS
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// FILE HEADER
# include <fcntl.h>

// PROCESS HEADERS
# include <sys/wait.h>

# define PROMPT_DISPLAY_TEXT "MINI_PROMPT: "

typedef struct s_ms {
	t_list	*cmdlist;
	char	**envp;
	int		*exit_code;
}	t_ms;

typedef struct s_tkn {
	char	*value;
	char	*token;
}	t_tkn;

char	**parse(char	*prompt);
void	init_signal_handlers(void);
char	*lookfor_error(t_list *tokens);

// BUILTINS
int		cd(int argc, char *argv[]);
int		echo(int argc, char *argv[]);
int		env(void);
int		export(char **argv);
int		pwd(void);
int		unset(char **argv);

#endif