/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:12:35 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/29 16:05:13 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defines.h"
# include "includes.h"

// BUILTINS
int		pwd(void);
int		cd(char **argv);
int		echo(char **argv);
int		env(void);
int		ms_exit(char **argv);
int		export(char **argv);
int		unset(char **argv);

//	INIT
t_ms	init_minishell(char **env);
char	*replace_env_variables(char *node);
void	init_signal_handlers(int flag);

// PARSE
char	**parse(char	*prompt);
char	*find_end_of_prompt(char *prompt, int quotes_flag);
char	*expand_variable(char *input, char *dollar);
int		syntax_analize(char **input);

// BUILD_CMD_LIST
t_list	*build_cmd_list(char **inputs);
t_cmd	*cast_cmd(t_list *node);
char	*find_cmd_path(char **env, char	*command);

// RUNNER
void	runner(t_list *list);
void	run_cmd(t_cmd *cmd, t_cmd *next);

// HELPER
void	free_table(char **table);
char	**append_table(char **table, char *variable);
char	**pop_table(char **table, char *address);
char	*join_var(char *before, char *variable, char *after);
char	**copy_environment(char **env);
char	**set_value(char **env, char *value);
char	**unset_value(char **env, char *key);
char	**update_value(char **env, char *variable);
char	*get_value(char **env, char *key);
void	close_fd(int fd);

// REDIRECT.H
int		file_to_stdin(char *filepath, int current_fd);
int		heredoc_to_stdin(char *stop_str, int current_fd);
int		stdout_to_file(char *filepath, int current_fd);
int		append_stdout_to_file(char *filepath, int current_fd);
int		redirect_single(t_cmd *cmd, int temp_fd);
void	redirect_fds(t_cmd *cmd, t_cmd *next);

// TOKEN_TYPE.H
int		is_token(char *string);
int		is_redirect(char *token);
int		is_builtin(char *cmd_str);
void	free_node(void *content);

#endif
