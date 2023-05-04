/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 21:50:02 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/05/03 22:04:47 by lbiasuz          ###   ########.fr       */
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

void	runner(t_list *token, int pid, int fd[2], int ofd[2])
{
	t_list	*node;
	char	*error;
	int		child_status;

	error = lookfor_error(token);
	if (error)
	{
		perror(error);
		return ;
	}
	node = return_pipe_or_null(token);
	if (node)
	{
		ofd[0] = fd[0];
		ofd[1] = fd[1];
		pipe(fd);
	}
	pid = fork();
	if (pid == 0)
		invoke_child(token, fd, ofd);
	if (fd[1] >= 3)
		close(fd[1]);
	if (ofd[0] >= 3)
		close(ofd[0]);
	if (node && pid != 0)
		runner(node->next, pid, fd, ofd);
	waitpid(0, &child_status, 0);
	close(fd[0]);
	close(ofd[1]);
}
