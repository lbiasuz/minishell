/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:23:22 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/01 08:53:13 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirect_fds(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->raw[i] && ft_strncmp(cmd->raw[i], PIPE, sizeof(PIPE)))
	{
		if (!ft_strncmp(cmd->raw[i], ICHEV, sizeof(ICHEV)))
			cmd->fd[0] = file_to_stdin(cmd->raw[i + 1], cmd->fd[0]);
		else if (!ft_strncmp(cmd->raw[i], DICHEV, sizeof(DICHEV)))
			cmd->fd[0] = heredoc_to_stdin(cmd->raw[i + 1], cmd->fd[0]);
		else if (!ft_strncmp(cmd->raw[i], CHEV, sizeof(CHEV)))
			cmd->fd[1] = stdout_to_file(cmd->raw[i + 1], cmd->fd[1]);
		else if (!ft_strncmp(cmd->raw[i], DCHEV, sizeof(DCHEV)))
			cmd->fd[1] = append_stdout_to_file(cmd->raw[i + 1], cmd->fd[1]);
		i++;
	}
	dup2(cmd->fd[0], STDIN_FILENO);
	dup2(cmd->fd[1], STDOUT_FILENO);
}
