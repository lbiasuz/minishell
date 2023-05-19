/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmiranda <rmiranda@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:30:21 by rmiranda          #+#    #+#             */
/*   Updated: 2023/05/19 11:30:23 by rmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tester.h"

extern t_info	g_info;

void	apply_test(int *fd)
{
	FILE	*file_to_open;
	char	*line;

	line = NULL;
	file_to_open = fopen(g_info.file_path, "r");
	if (!file_to_open)
	{
		printf("ERROR OPENING THE FILE\n");	
		return ;
	}
	while (getline(&line, NULL, file_to_open) > 1)
	{
		write(*fd, line, strlen(line));
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	fclose(file_to_open);
	write(*fd, "echo hello\n", 11);
}
