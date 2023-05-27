/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tester.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:37:41 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/26 11:05:36 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// commands learned: i shift-i a shift-a o shift-o u ctrl-r r w b dd v shift-v
// y p shift-zz shift->>/<<
// commands to learn: shift-u

#ifndef MINISHELL_TESTER_H
# define MINISHELL_TESTER_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <libft.h>
# include <get_next_line.h>

typedef struct s_info {
	int		pid;
	int		pipe[2];
	int		pipe2[2];
	char	*file_path;
	int		file_fd[2];
}	t_info;

void	apply_test(int *fd);

#endif
