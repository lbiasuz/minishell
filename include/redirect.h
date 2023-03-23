/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:51:18 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/21 21:34:06 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include <fcntl.h>

/// @brief Opens file from recieved path (Read only)
/// 		and duplicates content to STDIN
/// @param filepath 
/// @return fd returns opened fd
int	file_to_stdin(char *filepath);

/// @brief Waits for the user to type the content in the terminal,
///			until defined token is found;
/// @param token string with tells here-doc the user finished typing.
/// @return fd returns opened fd
int	here_doc_to_stdin(char *token);

/// @brief Opens/Creates file on recieved path (Write Only)
/// 		and duplicates the content from STDOUT to it;
/// @param filepath 
/// @return fd returns opened fd
int	stdout_to_file(char *filepath);

/// @brief Opens/Creates file on recieved path (Write Only)
/// 		and appends the content of STDOUT to file;
/// @param filepath 
/// @return fd returns opened fd
int	append_stdout_to_file(char *filepath);

#endif