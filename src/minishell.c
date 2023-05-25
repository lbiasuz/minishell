/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:30:16 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/22 21:02:44 by lbiasuz          ###   ########.fr       */
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

void	ft_dup2_and_close(int fd_to_close, int fd_to_dup)
{
	dup2(fd_to_close, fd_to_dup);
	if (fd_to_close > 0)
		close(fd_to_close);
}

void	dup_stdin_out(int *fds_to_restore)
{
	fds_to_restore[0] = dup(STDIN_FILENO);
	fds_to_restore[1] = dup(STDOUT_FILENO);
}

void	restore_stdin_out(int	*fds_to_restore)
{
	ft_dup2_and_close(fds_to_restore[0], STDIN_FILENO);
	ft_dup2_and_close(fds_to_restore[1], STDOUT_FILENO);
}

static int	process_input(char *prompt)
{
	char	**parsed_input;
	int	fds_to_restore[2];

	if (!prompt[0] || is_only_space(prompt))
		return (0);
	parsed_input = parse(prompt);
	add_history(prompt);
	free(prompt);
	dup_stdin_out(fds_to_restore);
	g_ms.commands = build_cmd_list(parsed_input, fds_to_restore);
	restore_stdin_out(fds_to_restore);
	free_table(parsed_input);
	free(parsed_input);
	runner(g_ms.commands);
	ft_lstclear((t_list **)&g_ms.commands, &free_node);
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
