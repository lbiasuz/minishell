/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/05 17:16:56 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

static int	process_input(char *prompt);
static void	print_parse(char **input);
static void	free_parse(char **input);
static void	print_tokens(t_list *tokens);

int	main(int argc, char *argv[])
{
	char	*prompt;

	(void)argv;
	if (argc >= 2)
		return (-1);
	init_signal_handlers();
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
		prompt = readline(PROMPT_DISPLAY_TEXT);
	}
	if (prompt)
		free(prompt);
	write(1, "\n", 1);
	rl_redisplay();
	clear_history();
	return (0);
}

static int	process_input(char *prompt)
{
	char	**parsed_input;
	t_list	*tokens;

	parsed_input = parse(prompt);
	tokens = tokenize(parsed_input);
	if (parsed_input)
	{
		add_history(prompt);
		print_parse(parsed_input);
		ft_printf("error: \x1B[37m%s\n", lookfor_error(tokens));
		print_tokens(tokens);
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

static void print_tokens(t_list *tokens)
{
	t_list	*l;
	t_tkn	*t;

	l = tokens;
	while (l)
	{
		t = l->content;
		ft_printf("token:\x1B[31m %s\x1B[0m + value:\x1B[31m %s \x1B[0m \n", t->token, t->value);
		l = l->next;
	}
}