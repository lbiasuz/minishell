/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/25 15:45:07 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	process_input(char *prompt);
static int	print_parse(char **input);
static int	free_parse(char **input);

int	main(int argc, char *argv[])
{
	char	*prompt;

	(void)argv;
	if (argc >= 2)
		return (-1);
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
	add_history(prompt);
	parsed_input = parse(prompt);
	if (parsed_input)
	{
		print_parse(parsed_input);
		free_parse(parsed_input);
	}
	rl_on_new_line();
	return (0);
}

static int	free_parse(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		free(input[i]);
		input[i] = NULL;
		i++;
	}
	return (0);
}

static int	print_parse(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		ft_printf("%s ", input[i++]);
	ft_printf("\n", input[i]);
	return (0);
}
