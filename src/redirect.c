/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:23:22 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/04/06 11:44:26 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <redirect.h>

int	file_to_stdin(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
	{
		perror("File not found");
		return (fd);
	}
	dup2(fd, STDIN_FILENO);
	return (fd);
}

int	stdout_to_file(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
	{
		perror("File not found");
		return (fd);
	}
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	heredoc_to_stdin(t_tkn token)
{
	char	*buff;
	char	*stop_str;
	int		stop_str_len;

	buff = "";
	stop_str = token.value;
	stop_str_len = ft_strlen(token.value);
	while (ft_strncmp(stop_str, buff, stop_str_len))
	{
		rl_on_new_line();
		buff = readline("heredoc> ");
		if (!buff)
			return (-1);
		write(STDIN_FILENO, buff, ft_strlen(buff));
	}
	return (0);
}

int	append_stdout_to_file(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
	{
		perror("File not found");
		return (fd);
	}
	dup2(fd, STDOUT_FILENO);
	return (fd);
}
