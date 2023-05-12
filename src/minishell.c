/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/12 15:48:32 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	process_input(char *prompt);
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
	prompt = readline(PROMPT_DISPLAY_TEXT);
	while (1)
	{
		if (!prompt || ft_strncmp("exit", prompt, 5) == 0)
		{
			write(1, "exit", 4);
			break ;
		}
		if (process_input(prompt))
			break ;
		free(prompt);
		rl_on_new_line();
		prompt = readline(PROMPT_DISPLAY_TEXT);
	}
	if (prompt)
		free(prompt);
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
	commands = tokenize(parsed_input);
	runner(commands);
	return (0);
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
