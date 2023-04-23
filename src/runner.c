/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/23 09:46:25 by lbiasuz          ###   ########.fr       */
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
		expand_token_content(last_node);
		command = find_cmd_path(g_ms.envp, ft_strtrim(gvle(last_node), " "));
	}
	return (command);
}

char	**get_args(t_list *list)
{
	t_list	*node;
	t_list	*last_node;
	char	**args;

	args = append_table(NULL, get_command(list));
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

void	invoke_child(t_list *tokens, int in_fd, int out_fd)
{
	char	*command;
	char	**args;

	command = get_command(tokens);
	args = get_args(tokens);
	if (command)
	{
		redirect_fds(tokens, in_fd, out_fd);
		g_ms.exit_code = execve(command, args, g_ms.envp);
	}
	exit(g_ms.exit_code);
}

void	runner(t_list *token, int pid, int fd[2], int ofd[2])
{
	t_list	*node;

	node = token;
	while (node && pid != 0)
	{
		if (!ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)))
			break ;
		node = node->next;
	}
	if (node && !ft_strncmp(gtkn(node), PIPE, sizeof(PIPE)) && pid != 0)
	{
		ofd[0] = fd[0];
		ofd[1] = fd[1];
		pipe(fd);
		pid = fork();
	}
	else if (!node && pid != 0)
		pid = fork();
	if (pid == 0)
		invoke_child(token, ofd[0], fd[1]);
	if (pid != 0 && node)
		runner(node->next, pid, fd, ofd);
	if (pid != 0 && !node)
		wait(0);
}
