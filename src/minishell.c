/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/03/23 21:55:42 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		process_input(char *prompt);
char	**parse_and_free_prompt(char	*prompt);
int		execute_and_free_instruction(char **input);

int	main(int argc, char *argv[])
{
	int		limiter = 2;

	(void)argv;
	if (argc >= 2)
		return (-1);
	while (limiter-- && !process_input(readline("MINI_PROMPT:")))
		;
	return (0);
}

int	process_input(char *prompt)
{
	char	**input;

	if (prompt == NULL)
		return (-1);
	input = parse(prompt);
	free(prompt);
	if (!input)
	{
		perror("error on parse");
		exit(-1);
	}
	execute_and_free_instruction(input);
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
