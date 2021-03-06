/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:20:23 by bmangin           #+#    #+#             */
/*   Updated: 2021/06/14 21:23:57y bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lstadd_frt(t_lst **lst, t_lst *new)
{
	new->next = *lst;
	*lst = new;
}

t_lst	*lst_new(float x, float y, int id)
{
	t_lst	*lst;

	lst = wrmalloc(sizeof(t_lst));
	if (lst)
	{
		lst->x = x + 0.5;
		lst->y = y + 0.5;
		lst->id = id;
		lst->next = NULL;
	}
	return (lst);
}

void	clear_lst(t_lst **lst)
{
	t_lst	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		wrfree(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	in_lst(t_lst *lst, float x, float y)
{
	while (lst)
	{
		if (lst->x == x + 0.5 && lst->y == y + 0.5)
			return (1);
		lst = lst->next;
	}
	return (0);
}

int	lst_size(t_lst *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
