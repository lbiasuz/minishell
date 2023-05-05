/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/05 10:02:50 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms g_ms;

int	is_redirect(char *token)
{
	if (!token)
		return (0);
	return (!ft_strncmp(token, DICHEV, sizeof(DICHEV))
		|| !ft_strncmp(token, DCHEV, sizeof(DCHEV))
		|| !ft_strncmp(token, CHEV, sizeof(CHEV))
		|| !ft_strncmp(token, ICHEV, sizeof(ICHEV)));
}


t_list	*return_pipe_or_null(t_list	*token)
{
	while (token)
	{
		if (!ft_strncmp(gtkn(token), PIPE, sizeof(PIPE)))
			break ;
		token = token->next;
	}
	return (token);
}

int	is_command(char	*token, char *last_token)
{
	if (!token)
		return (0);
	return (!is_redirect(last_token)
		&& (!ft_strncmp(token, EXPAND, sizeof(EXPAND))
			|| !ft_strncmp(token, TEXT, sizeof(TEXT))
			|| !ft_strncmp(token, SQUOTE, sizeof(SQUOTE))
			|| !ft_strncmp(token, DQUOTE, sizeof(DQUOTE)))
	);
}

int	is_arg(char *token, char *last_token)
{
	if (!token || !last_token)
		return (0);
	return ((!ft_strncmp(token, EXPAND, sizeof(EXPAND))
			|| !ft_strncmp(token, TEXT, sizeof(TEXT))
			|| !ft_strncmp(token, SQUOTE, sizeof(SQUOTE))
			|| !ft_strncmp(token, DQUOTE, sizeof(DQUOTE)))
		&& (!ft_strncmp(last_token, EXPAND, sizeof(EXPAND))
			|| !ft_strncmp(last_token, TEXT, sizeof(TEXT))
			|| !ft_strncmp(last_token, SQUOTE, sizeof(SQUOTE))
			|| !ft_strncmp(last_token, DQUOTE, sizeof(DQUOTE)))
	);
}

char	*get_command(t_list *list)
{
	t_list	*node;
	t_list	*last_node;
	char	*command;

	node = list;
	last_node = NULL;
	command = NULL;
	while (!command && node)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
			break ;
		if ((!last_node || !is_redirect(gtkn(last_node)))
			&& (!is_redirect(gtkn(node))
				&& is_command(gtkn(node), gtkn(last_node))))
			command = ft_strtrim(gvle(node), " ");
		last_node = node;
		node = node->next;
	}
	expand_token_content(last_node);
	if (command)
		command = find_cmd_path(g_ms.envp, ft_strtrim(gvle(last_node), " "));
	return (command);
}

char	**get_args(t_list *list, char **args)
{
	t_list	*node;
	t_list	*last_node;

	last_node = NULL;
	node = list;
	while (node)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
			break ;
		if (is_arg(gtkn(node), gtkn(last_node)))
		{
			expand_token_content(node);
			args = append_table(args, ft_strtrim(gvle(node), " "));
		}
		last_node = node;
		node = node->next;
	}
	return (args);
}

void	invoke_child(t_list *tokens, int fd[2], int ofd[2])
{
	char	*command;
	char	**args;

	command = get_command(tokens);
	args = get_args(tokens, append_table(NULL, command));
	if (command && args)
	{
		redirect_fds(tokens, fd, ofd);
		g_ms.exit_code = execve(command, args, g_ms.envp);
	}
	exit(g_ms.exit_code);
}

void	runner(char	**parsed_input)
{
	t_cmd	command;

	command.str_table = compose_str_table(parsed_input);
	command.str = compose_str(parsed_input);
	setup_fds(&parsed_input);
	setup_pipes(&parsed_input);
	command.exec_exit_code = exec_command(command);

}

t_fd	setup_pipes(t_cmd	*command)
{
	t_fd	fds;
	char	*pipe_address;

	fds.in = 0;
	fds.out = 0;
	pipe_address = return_pipe_or_null(command->str_table);
	if (pipe_address)
	{
		command->ofds.in = command->fds.in;
		command->ofds.out = command->fds.out;
		return (pipe((int *)&command->fds));
	}
	return (0);
}

int	exec_command(t_cmd command)
{
	int		pid;

	command.exec_exit_code = 0;
	pid = fork();
	if (pid == 0)
		command.exec_exit_code = invoke_child(token, (int *)&command.fds, (int *)&command.fds);
	else
	{
		waitpid(0, &command.exec_exit_code, 0);
		{
		if (command.fds.out >= 3)
			close(command.fds.out);
		if (command.ofds.in >= 3)
			close(command.ofds.in);
		if (command.fds.in >= 3)
			close(command.fds.in);
		if (command.ofds.out >= 3)
			close(command.ofds.out);
		}
		runner(return_pipe_or_null(command.str_table));
	}
	return (0);
}