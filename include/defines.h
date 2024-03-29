/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:37:40 by rmiranda          #+#    #+#             */
/*   Updated: 2023/06/03 14:40:35 by lbiasuz          ###   ########.fr       */
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
# define PROMPT_DISPLAY_TEXT "MINI_PROMPT: "
# define ERROR_CNF ": command not found\n"
# define ERROR_II ": not a valid identifier\n"
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

typedef struct sigaction	t_sigaction;

typedef struct s_ms {
	char	**envp;
	int		exit_code;
	int		exit_code_previous;
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
