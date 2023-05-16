/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/16 11:14:51 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	process_input(char *prompt);
static void	free_node_contents(void *node);
static char	*new_prompt_input(char **prompt_ptr);
// static void	print_parse(char **input);
// static void	print_tokens(t_list *tokens);

t_ms	g_ms;

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;

	(void)argv;
	if (argc >= 2)
		return (-1);
	init_signal_handlers();
	g_ms = init_minishell(envp);
	prompt = NULL;
	while (new_prompt_input(&prompt))
	{
		if (!prompt)
			break ;
		if (process_input(prompt))
		{
			free(prompt);
			break ;
		}
	}
	write(1, "\n", 1);
	clear_history();
	free_str_table(g_ms.envp);
	return (0);
}

static int	process_input(char *prompt)
{
	char	**parsed_input;
	t_list	*commands;

	parsed_input = parse(prompt);
	if (!parsed_input)
		return (0);
	if (syntax_analysis(parsed_input))
		return (0);
	add_history(prompt);
	commands = build_cmd_list(parsed_input);
	runner(commands);
	ft_lstclear(&commands, &free_node_contents);
	free_table(parsed_input);
	free(parsed_input);
	return (0);
}

static void	free_node_contents(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	if (cmd->exe)
		free(cmd->exe);
	if (cmd->exe_path)
		free(cmd->exe_path);
	if (cmd->args)
	{
		free_table(cmd->args);
		free(cmd->args);
	}
	if (cmd->raw)
	{
		free_table(cmd->raw);
		free(cmd->raw);
	}
	free(cmd);
}

static char	*new_prompt_input(char **prompt_ptr)
{
	if (*prompt_ptr)
	{
		free(*prompt_ptr);
		rl_on_new_line();
	}
	*prompt_ptr = readline(PROMPT_DISPLAY_TEXT);
	return (*prompt_ptr);
}

// static void	print_parse(char **input)
// {
// 	int	i;

// 	i = 0;
// 	while (input[i])
// 		ft_printf("%s ", input[i++]);
// 	ft_printf("\n", input[i]);
// }

// static void	print_tokens(t_list *tokens)
// {
// 	t_list	*l;
// 	t_tkn	*t;

// 	l = tokens;
// 	while (l)
// 	{
// 		t = l->content;
// 		if (!ft_strncmp(t->token, EXPAND, sizeof(EXPAND)))
// 			t->token = expand_variable(t->value, ft_strchr(t->value, '$'));
// 		ft_printf(
// 			"token:\x1B[31m %s\x1B[0m + value:\x1B[31m %s \x1B[0m \n",
// 			t->token,
// 			t->value
// 			);
// 		l = l->next;
// 	}
// }
