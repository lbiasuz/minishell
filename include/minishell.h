/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:12:35 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/21 20:51:00 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/ft_printf.h"

// READLINE FUNCTION HEADERS
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// FILE HEADER
# include <fcntl.h>

// PROCESS HEADERS
# include <sys/wait.h>


typedef struct s_ms {
	t_list	*cmdlist;
	char	**envp;
	int		*exit_code;
}	t_ms;

typedef struct s_cmd {
	char	*command;
	char	**args;
	int		err_fd;
	int		out_fd;
	int		in_fd;
}	t_cmd;

#endif