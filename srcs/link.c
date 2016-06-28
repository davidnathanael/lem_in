/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 15:50:45 by adompe            #+#    #+#             */
/*   Updated: 2016/06/24 12:14:37 by adompe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool			ft_is_link(char **tab, t_lem_in *data)
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
		if (ft_strcmp(tab[1], room->name) == 0 && ft_strcmp(tab[1], tab[0]))
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

static void		ft_include_link(char *s1, char *s2, t_lem_in *data)
{
	t_room *room;
	t_list *tmp;

	tmp = data->rooms;
	while (tmp)
	{
		room = tmp->content;
		if (ft_strcmp(room->name, s1) == 0)
		{
			if (!room->linked_rooms)
				room->linked_rooms = ft_lstnew(s2, ft_strlen(s2) + 1);
			else
				ft_lstadd(&room->linked_rooms,
				ft_lstnew(s2, ft_strlen(s2) + 1));
		}
		tmp = tmp->next;
	}
}

void			ft_get_link_rooms(t_lem_in *data)
{
	char	*buf;
	char	**tab;

	buf = NULL;
	if (!ft_is_comment(data->buf) && data->buf)
	{
		tab = ft_strsplit(data->buf, '-');
		if (!ft_is_link(tab, data))
			return ;
		ft_include_link(tab[0], tab[1], data);
		ft_include_link(tab[1], tab[0], data);
	}
	while (get_next_line(0, &buf))
	{
		ft_lstappend(&data->to_print, ft_lstnew(buf, ft_strlen(buf) + 1));
		if (ft_is_comment(buf))
			continue ;
		tab = ft_strsplit(buf, '-');
		if (!ft_is_link(tab, data))
			return ;
		ft_include_link(tab[0], tab[1], data);
		ft_include_link(tab[1], tab[0], data);
	}
}
