/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/04 19:28:50 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	process_input(char *prompt);
static void	print_parse(char **input);
static void	free_parse(char **input);

int	main(int argc, char *argv[])
{
	char	*prompt;

	(void)argv;
	if (argc >= 2)
		return (-1);
	init_signal_handlers();
	prompt = readline("MINI_PROMPT:");
	while (prompt)
	{
		if (ft_strncmp("exit", prompt, 5) == 0)
			break ;
		if (process_input(prompt))
			break ;
		free(prompt);
		prompt = readline("MINI_PROMPT:");
	}
	if (prompt)
		free(prompt);
	clear_history();
	return (0);
}

static int	process_input(char *prompt)
{
	char	**parsed_input;

	if (!*prompt)
		return (0);
	parsed_input = parse(prompt);
	if (parsed_input)
	{
		add_history(prompt);
		print_parse(parsed_input);
		free_parse(parsed_input);
	}
	rl_on_new_line();
	return (0);
}

static void	free_parse(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		input[i] = NULL;
		i++;
	}
}

static void	print_parse(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		ft_printf("%s ", input[i++]);
	ft_printf("\n", input[i]);
}
