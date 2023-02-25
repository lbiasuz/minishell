/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:33:03 by lbiasuz           #+#    #+#             */
/*   Updated: 2022/04/26 00:11:34 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **list, void (*del)(void *))
{
	t_list	*next;

	if (!(*list))
		return ;
	next = (*list)->next;
	del((*list)->content);
	free(*list);
	*list = next;
	ft_lstclear(list, del);
}
