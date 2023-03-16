/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/16 10:31:15 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		process_input(char *prompt);
char	**parse_and_free_prompt(char	*prompt);
int		execute_and_free_instruction(char **input);

int	main(int argc, char *argv[])
{
	(void)argv;
	if (argc >= 2)
		return (-1);
	while (!process_input(readline("MINI_PROMPT:")))
		;
	return (0);
}

int	process_input(char *prompt)
{
	char **input;

	if (prompt == NULL)
		return (-1);
	input = parse_and_free_prompt(prompt);
	if (!input)
	{
		perror("error on ft_split");
		exit(-1);
	}
	execute_and_free_instruction(input);
	return (0);
}

char	**parse_and_free_prompt(char	*prompt)
{
	char	**split_result;

	split_result = ft_split(prompt, ' ');
	free(prompt);
	return (split_result);
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