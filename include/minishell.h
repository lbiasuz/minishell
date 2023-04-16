/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:12:35 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/15 21:03:38 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CHEV ">"
# define DCHEV ">>"
# define ICHEV "<"
# define DICHEV "<<"
# define SQUOTE "\'"
# define DQUOTE "\""
# define PIPE "|"
# define SEMI ";"
# define DOLL "$"
# define ECOM "&"
# define TEXT "TEXT"
# define EXPAND "EXPAND"
# define ERROR "Syntax error"
# define HOME "~"
# define NL "newline"

# include <libft.h>
# include <ft_printf.h>

// READLINE FUNCTION HEADERS
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

// FILE HEADER
# include <fcntl.h>

# include <stdio.h>
# include <unistd.h>

// PROCESS HEADERS
# include <sys/wait.h>

# define PROMPT_DISPLAY_TEXT "MINI_PROMPT: "

typedef struct s_ms {
	t_list	*cmdlist;
	t_list	*tokenlist;
	char	**envp;
	int		*exit_code;
}	t_ms;

typedef struct s_tkn {
	char	*value;
	char	*token;
}	t_tkn;

//	INIT
t_ms	init_minishell(char **env);

char	**parse(char	*prompt);
void	init_signal_handlers(void);
char	*lookfor_error(t_list *tokens);

// BUILTINS
int		cd(int argc, char *argv[]);
int		echo(int argc, char *argv[]);
int		env(void);
int		export(char **argv);
int		pwd(void);
int		unset(char **argv);

//HELPER
char	**char_occurences(char *string, char c);
int		char_count(char *string, char c);
void	free_table(char **table);
char	*gtkn(t_list *node);
char	*gvle(t_list *node);

char	*expand_variable(char *input, char *dollar);

char	*find_cmd_path(char **env, char	*command);

void	runner(t_list *token_list);

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

void	redirect_fds(t_list *tokens, int in_fd, int out_fd);

//TOKEN.H
t_list	*plain_token(char *input);
t_list	*compose_token(char *input);
t_list	*tokenize(char **inputs);

#endif