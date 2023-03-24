/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/23 22:57:09 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		process_input(char *prompt);
char	**parse_and_free_prompt(char	*prompt);
int		execute_and_free_instruction(char **input);

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

int	process_input(char *prompt)
{
	char	**input;

	if (!*prompt)
		return (0);
	add_history(prompt);
	input = parse(prompt);
	if (!input)
	{
		perror("error on parse");
		exit(-1);
	}
	execute_and_free_instruction(input);
	rl_on_new_line();
	return (0);
}

int	execute_and_free_instruction(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_printf("%s ", input[i]);
		free(input[i++]);
	}
	ft_printf("\n", input[i]);
	free(input);
	return (0);
}
