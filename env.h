/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:42:06 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/02/26 16:44:16 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft/libft.h"

char	**copy_environment(char **env);
//Sets new enviroment variable or updates existing one;
char	**set_value(char **env, char **value);
//Deletes variable form list.
char	**unset_value(char **env, char *key);

#endif