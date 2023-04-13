/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:51:18 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/13 11:47:42 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

/// @brief Opens file from recieved path (Read only)
/// 		and duplicates content to STDIN
/// @param filepath 
/// @return fd returns opened fd
int	file_to_stdin(char *filepath, int current_fd);

/// @brief Waits for the user to type the content in the terminal,
///			until defined token is found;
/// @param token string with tells here-doc the user finished typing.
/// @return fd returns opened fd
int	heredoc_to_stdin(char *stop_str, int current_fd);

/// @brief Opens/Creates file on recieved path (Write Only)
/// 		and duplicates the content from STDOUT to it;
/// @param filepath 
/// @return fd returns opened fd
int	stdout_to_file(char *filepath, int current_fd);

/// @brief Opens/Creates file on recieved path (Write Only)
/// 		and appends the content of STDOUT to file;
/// @param filepath 
/// @return fd returns opened fd
int	append_stdout_to_file(char *filepath, int current_fd);

void	redirect_fds(t_list *tokens, int in_fd, int out_fd);

#endif