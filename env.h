/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:42:06 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/02/28 11:19:13 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft/libft.h"

/// @brief Copies an array of strings to heap.
/// @param env Array of strings, NULL terminated.
/// @return Exact copy of the first array.
char	**copy_environment(char **env);

/// @brief Sets target variable into array of strings,
/// tries to update an existing key first, if it fails, adds it instead;
/// @param env Array os strings, NULL terminated;
/// @param variable String composed by a key/value pair separated by '=';
/// @return New array of string, with target updated/added;
char	**set_value(char **env, char **value);

/// @brief Removes designated variable from array of strings;
/// @param env Array of strings, NULL terminated;
/// @param key Beggining of the target string, must end in '=';
/// @return New array of string, with target removed;
char	**unset_value(char **env, char *key);

/// @brief Tries to update from table a string which matches variable key;
/// @param env Array of strings, NULL terminated;
/// @param variable String composed by a key/value pair separated by '=';
/// @return Returns the updated string table,
/// NULL if no string is found to update;
char	**update_value(char **env, char **variable);

void	free_env(char **env);

#endif