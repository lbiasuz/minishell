/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/17 12:04:05 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_ms g_ms;

int	is_command(char	*token, char *last_token)
{
	if (!token)
		return (0);
	ft_printf("IS COMMAND: %s %s \n", token, last_token);
	return (ft_strncmp(last_token, DICHEV, sizeof(DICHEV))
		&& ft_strncmp(last_token, DCHEV, sizeof(DCHEV))
		&& ft_strncmp(last_token, CHEV, sizeof(CHEV))
		&& ft_strncmp(last_token, ICHEV, sizeof(ICHEV))
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
	ft_printf("node %p", node);
	while (!command && node)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
			break ;
		if (!last_node || is_command(gtkn(node), gtkn(last_node)))
			command = gvle(node);
		last_node = node;
		node = node->next;
	}
	if (command)
	{
		expand_token_content(node);
		command = find_cmd_path(g_ms.envp, gvle(node));
	}
	return (command);
}

char	**get_args(t_list *list)
{
	t_list	*node;
	t_list	*last_node;
	char	**args;

	args = NULL;
	last_node = NULL;
	node = list;
	while (node)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
			break ;
		if (is_arg(gtkn(node), gtkn(last_node)))
		{
			expand_token_content(node);
			args = append_table(args, gvle(node));
		}
		last_node = node;
		node = node->next;
	}
	return (args);
}

static void	print_tokens(t_list *tokens)
{
	t_list	*l;
	t_tkn	*t;

	l = tokens;
	while (l)
	{
		t = l->content;
		if (!ft_strncmp(t->token, EXPAND, sizeof(EXPAND)))
			t->token = expand_variable(t->value, ft_strchr(t->value, '$'));
		ft_printf(
			"token:\x1B[31m %s\x1B[0m + value:\x1B[31m %s \x1B[0m \n",
			t->token,
			t->value
			);
		l = l->next;
	}
}

void	invoke_child(t_list *tokens, int in_fd, int out_fd)
{
	redirect_fds(tokens, in_fd, out_fd);
	print_tokens(tokens);
	g_ms.exit_code = execve(get_command(tokens), get_args(tokens), g_ms.envp);
}

void	runner(t_list *token_list)
{
	t_list	*node;
	int		pid;
	int		old_fd[2];
	int		fd[2];

	node = token_list;
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	old_fd[0] = STDIN_FILENO;
	old_fd[1] = STDOUT_FILENO;
	pid = -1;
	while (pid != 0 && node)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)) && pid != 0)
		{
			old_fd[0] = fd[0];
			old_fd[1] = fd[1];
			pipe(fd);
			pid = fork();
		}
		else if (!node->next && pid != 0)
			pid = fork();
		node = node->next;
	}
	if (pid == 0 && node)
		invoke_child(node, old_fd[0], fd[1]);
	if (pid == 0 && !node)
		invoke_child(token_list, old_fd[0], STDOUT_FILENO);
	if (pid == 0)
		exit(g_ms.exit_code);
	else
		wait(0);
}