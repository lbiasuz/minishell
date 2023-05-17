/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:12:35 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/17 07:30:23 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defines.h"
# include "includes.h"

//	INIT
t_ms	init_minishell(char **env);

int		syntax_analysis(char **parsed_input);
char	**parse(char	*prompt);
void	init_signal_handlers(void);

// BUILTINS
int		pwd(void);
int		cd(char **argv);
int		echo(char **argv);
int		env(void);
int		ms_exit(char **argv);
int		export(char **argv);
int		unset(char **argv);

//HELPER
char	**char_occurences(char *string, char c);
int		char_count(char *string, char c);
void	free_table(char **table);
char	**append_table(char **table, char *variable);
char	**pop_table(char **table, char *address);
char	*join_envp_var(char *before, char *variable, char *after);

char	*expand_variable(char *input, char *dollar);
char	*find_cmd_path(char **env, char	*command);
char	*exp_str_content(char *node);

void	runner(t_list *list);
void	run_cmd(t_cmd *cmd, t_cmd *next);

// ENV.H
/// @brief Copies an array of strings to heap.
/// @param env Array of strings, NULL terminated.
/// @return Exact copy of the first array.
char	**copy_environment(char **env);

/// @brief Sets target variable into array of strings,
/// tries to update an existing key first, if it fails, adds it instead;
/// @param env Array os strings, NULL terminated;
/// @param variable String composed by a key/value pair separated by '=';
/// @return New array of string, with target updated/added;
char	**set_value(char **env, char *value);

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
char	**update_value(char **env, char *variable);

/// @brief Retrieves content from envirnment variable;
/// @param env Array of strings, NULL terminated;
/// @param key Beggining of the target string;
/// @return Returns the desired value, NULL if key is not found,
char	*get_value(char **env, char *key);

// REDIRECT.H
/// @brief Opens file from recieved path (Read only)
/// 		and duplicates content to STDIN
/// @param filepath 
/// @return fd returns opened fd
int		file_to_stdin(char *filepath, int current_fd);

/// @brief Waits for the user to type the content in the terminal,
///			until defined token is found;
/// @param token string with tells here-doc the user finished typing.
/// @return fd returns opened fd
int		heredoc_to_stdin(char *stop_str, int current_fd);

/// @brief Opens/Creates file on recieved path (Write Only)
/// 		and duplicates the content from STDOUT to it;
/// @param filepath 
/// @return fd returns opened fd
int		stdout_to_file(char *filepath, int current_fd);

/// @brief Opens/Creates file on recieved path (Write Only)
/// 		and appends the content of STDOUT to file;
/// @param filepath 
/// @return fd returns opened fd
int		append_stdout_to_file(char *filepath, int current_fd);

void	redirect_fds(t_cmd *cmd, t_cmd *next);
void	close_fd(int fd);

// BUILD_CMD_LIST
t_list	*build_cmd_list(char **inputs);
t_cmd	*cast_cmd(t_list *node);

// TOKEN_TYPE.H
int		is_token(char *string);
int		is_redirect(char *token);
int		is_command(char *string);
int		is_arg(char *token, char *last_token, t_cmd cmd);
int		byp_builtin(char *cmd_str);
void	free_node_contents(void *content);


#endif