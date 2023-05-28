/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:37:40 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/29 01:05:06 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# include <libft.h>

# define CHEV ">"
# define DCHEV ">>"
# define ICHEV "<"
# define DICHEV "<<"
# define SQUOTE "\'"
# define DQUOTE "\""
# define PIPE "|"
# define SEMI ";" // not to be handled
# define DOLL "$"
# define ECOM "&"
# define TEXT "TEXT"
# define EXPAND "EXPAND"
# define ERROR "Syntax error"
# define HOME "~"
# define NL "newline"
# define PROMPT_DISPLAY_TEXT "MINI_PROMPT: "
# define ERROR_CNF ": command not found\n"
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

typedef struct s_ms {
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