/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 15:50:45 by adompe            #+#    #+#             */
/*   Updated: 2016/06/16 15:50:49 by adompe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool		ft_is_link(char **tab, t_lem_in *data)
{
	t_list	*tmp;
	t_room	*room;

	tmp = data->rooms;
	if (ft_tablen(tab) != 2)
		return (FALSE);
	while (tmp)
	{
		room = tmp->content;
		if (ft_strcmp(tab[0], room->name) == 0)
			break ;
		if (tmp->next == NULL)
			return (FALSE);
		tmp = tmp->next;
	}
	tmp = data->rooms;
	while (tmp)
	{
		room = tmp->content;
		if (ft_strcmp(tab[1], room->name) == 0 && ft_strcmp(tab[1], tab[0]) != 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

static void     ft_include_link(char *str, t_lem_in *data)
{
    t_room *room;
    t_list *tmp;

    tmp = data->rooms;
	while (tmp)
	{
		room = tmp->content;
		if (ft_strcmp(room->name, str) == 0)
		{
			if (!room->linked_rooms)
				room->linked_rooms = ft_lstnew(str, ft_strlen(str));
			else
				ft_lstadd(&room->linked_rooms, ft_lstnew(str, ft_strlen(str)));
		}
		tmp = tmp->next;
	}
}

void		ft_get_link_rooms(t_lem_in *data)
{
	char   *buf;
	char   **tab;

	buf = NULL;
    if (!ft_is_comment(buf) && data->buf)
    {
        tab = ft_strsplit(data->buf, '-');
		if (!ft_is_link(tab, data))
			return ;
        ft_include_link(tab[0], data);
        ft_include_link(tab[1], data);
    }
	while (get_next_line(0, &buf))
	{
        if (ft_is_comment(buf))
            continue ;
        tab = ft_strsplit(buf, '-');
		if (!ft_is_link(tab, data))
			return ;
        ft_include_link(tab[0], data);
        ft_include_link(tab[1], data);
	}
}
