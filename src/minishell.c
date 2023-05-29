/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/29 15:58:52 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	process_input(char *prompt);
static char	*new_prompt_input(char **prompt_ptr);
static int	is_only_space(char	*prompt);

t_ms	g_ms;

int	main(int argc, char *argv[], char *envp[])
{
	char	*prompt;

	(void)argv;
	if (argc >= 2)
		return (-1);
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

	if (!prompt[0] || is_only_space(prompt))
		return (0);
	parsed_input = parse(prompt);
	add_history(prompt);
	free(prompt);
	if (syntax_analize(parsed_input))
	{
		g_ms.commands = build_cmd_list(parsed_input);
		free_table(parsed_input);
		free(parsed_input);
		runner(g_ms.commands);
		ft_lstclear((t_list **)&g_ms.commands, &free_node);
	}
	else
	{
		free_table(parsed_input);
		free(parsed_input);
		ft_lstclear((t_list **)&g_ms.commands, &free_node);
		g_ms.exit_code = 2;
	}
	return (0);
}

static char	*new_prompt_input(char **prompt_ptr)
{
	rl_on_new_line();
	*prompt_ptr = readline(PROMPT_DISPLAY_TEXT);
	return (*prompt_ptr);
}

static int	is_only_space(char	*prompt)
{
	char	*original_ptr;

	original_ptr = prompt;
	while (ft_isspace(prompt[0]))
		prompt++;
	if (prompt[0])
		return (0);
	free(original_ptr);
	return (-1);
}
