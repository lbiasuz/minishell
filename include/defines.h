/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:37:40 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/29 20:27:05 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# include <libft.h>

# define CHEV ">"
# define DCHEV ">>"
# define ICHEV "<"
# define DICHEV "<<"
# define PIPE "|"
# define HOME "~"
# define PROMPT_DISPLAY_TEXT "\033[0;31m MINI_PROMPT: \033[0m"
# define ERROR_CNF ": command not found\n"
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

typedef struct sigaction	t_sigaction;

typedef struct s_ms {
	int		pid;
	char	**envp;
	int		exit_code;
	t_list	*commands;
}	t_ms;

typedef struct s_cmd {
	char	*exe;
	char	*exe_path;
	int		fd[2];
	char	**args;
	char	**raw;
}	t_cmd;

#endif
