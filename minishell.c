/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/12 19:11:21 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_instruction(char **input);
int		process_input(char *prompt);
char	*wait_for_input(void);
char	**parse_prompt(char	*prompt);

int	main(int argc, char *argv[])
{
	int	prompt_limit_deguuber = 5;
	if (argc >= 2)
		return (-1);
	while (!process_input(readline("MINI_PROMPT:")) && prompt_limit_deguuber--)
		;
	(void)argv;
	return (0);
}

int	process_input(char *prompt)
{
	char **input;

	if (prompt == NULL)
		return (-1);
	input = parse_prompt(prompt);
	free(prompt);
	if (input)
	{
		execute_instruction(input);
		free(input);
	}
	return (0);
}

char	**parse_prompt(char	*prompt)
{
	char	**split_result;

	split_result = ft_split(prompt, ' ');
	return (split_result);
}

int	execute_instruction(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_printf("%s ", input[i]);
		free(input[i++]);
	}
	return (0);
}