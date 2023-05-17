/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/17 16:52:41 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	process_input(char *prompt);
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
			break ;
	}
	write(1, "\n", 1);
	clear_history();
	free_table(g_ms.envp);
	free(g_ms.envp);
	return (0);
}

static int	process_input(char *prompt)
{
	char	**parsed_input;

	parsed_input = parse(prompt);
	add_history(prompt);
	free(prompt);
	g_ms.commands = (void *)build_cmd_list(parsed_input);
	free_table(parsed_input);
	free(parsed_input);
	runner((t_list *)g_ms.commands);
	ft_lstclear((t_list **)&g_ms.commands, &free_node_contents);
	return (0);
}

static char	*new_prompt_input(char **prompt_ptr)
{
	rl_on_new_line();
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
