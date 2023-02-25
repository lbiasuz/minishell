/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:42:06 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/02/25 19:49:14 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft/libft.h"

typedef struct s_env {
	char	*key;
	char	*value;
}	t_env;

//Returns list of variables as table os strings, for broad useage;
char	**get_env_as_table(t_list *env);
//Sets new enviroment variable or updates existing one;
void	set_value(t_list *env, char *key, char *value);
//Deletes variable form list.
void	unset_value(t_list *env, char *key);
//Helper function to clear t_list node content.
void	free_env_variable(t_env *var);

#endif