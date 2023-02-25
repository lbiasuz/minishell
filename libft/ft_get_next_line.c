/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 22:42:59 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/08/23 22:54:03 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_file(int fd, char **str_hold)
{
	char	*read_str;
	int		read_len;
	char	*temp;

	read_str = malloc((sizeof(char) * BUFFER_SIZE + 1));
	read_len = read(fd, read_str, BUFFER_SIZE);
	if (read_len < 0)
		return (read_len);
	read_str[read_len] = 0;
	if (!str_hold || !str_hold[0])
		str_hold[0] = read_str;
	else
	{
		temp = ft_strjoin_gnl(str_hold, &read_str);
		free(str_hold[0]);
		free(read_str);
		str_hold[0] = temp;
	}
	return (read_len);
}

char	*gen_line(char **str_hold)
{
	int		pos_nl;
	char	*output;
	char	*after_nl;

	pos_nl = ft_strchr_gnl(*str_hold, '\n');
	if (pos_nl >= 0)
	{
		after_nl = ft_substr_gnl(
				str_hold[0], pos_nl + 1, ft_strlen(str_hold[0] + pos_nl + 1)
				);
		output = ft_substr_gnl(str_hold[0], 0, pos_nl + 1);
		free(*str_hold);
		str_hold[0] = after_nl;
		return (output);
	}
	if (str_hold[0][0])
		output = ft_substr_gnl(str_hold[0], 0, ft_strlen(str_hold[0]));
	else
		output = NULL;
	free(str_hold[0]);
	str_hold[0] = NULL;
	return (output);
}

char	*get_next_line(int fd)
{
	int			read_len;
	static char	*str_hold[1024];

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, str_hold[fd], 0) < 0)
		return (NULL);
	read_len = 1;
	while (read_len)
	{
		read_len = read_file(fd, &str_hold[fd]);
		if (read_len < BUFFER_SIZE || ft_strchr_gnl(str_hold[fd], '\n') >= 0)
			read_len = 0;
	}
	return (gen_line(&str_hold[fd]));
}
