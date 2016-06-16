/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:40:27 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/06 16:40:28 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list			*ft_get_rooms(t_lem_in *data)
{
	char	*buf;
	t_room	*room;

	buf = NULL;
	room = NULL;
	data->rooms = NULL;
	while (get_next_line(0, &buf))
	{
		if (ft_is_valid_command(buf))
			ft_handle_command(buf, data);
		else if (ft_is_room(buf))
		{
			room = ft_extract_room(buf, data);
			if (!data->rooms)
				data->rooms = ft_lstnew((t_room *)room, sizeof(*room));
			else
				ft_lstadd(&data->rooms, ft_lstnew((t_room *)room, sizeof(*room)));
		}
		else if (ft_is_comment(buf))
			;
		else
		{
			data->buf = ft_strdup(buf);
			break;
		}
	}
	return (data->rooms);
}

static unsigned int		ft_get_nb_ants()
{
	char	*buf;
	int		nb_ants;

	buf = NULL;
	nb_ants = 0;
	while (get_next_line(0, &buf) && ft_is_comment(buf))
		;
	if ((nb_ants = ft_atoi(buf)) <= 0)
	{
		ft_printf("Error : Incorrect number of ants.\n");
		exit(0);
	}
	return (nb_ants);
}

void		ft_get_link_rooms(t_lem_in *data)
{
	char *buf;
	char 	**tab;
	t_list	*tmp;
	t_room	*room;

	tmp = data->rooms;
	buf = NULL;
	if (data->buf)
		buf = data->buf;
	while (get_next_line(0, &buf))
	{
		if (!ft_is_link(buf, data))
			return ;
		tab = ft_strsplit(buf, '-');
		while (tmp)
		{
			room = tmp->content;
			if (ft_strcmp(room->name, tab[0]) == 0)
			{
				if (!room->linked_rooms)
					room->linked_rooms = ft_lstnew(tab[1], ft_strlen(tab[1]));
				else
					ft_lstadd(&room->linked_rooms, ft_lstnew(tab[1], ft_strlen(tab[1])));
			}
			tmp = tmp->next;
		}
		tmp = data->rooms;
		while (tmp)
		{
			room = tmp->content;
			if (ft_strcmp(room->name, tab[1]) == 0)
			{
				if (!room->linked_rooms)
					room->linked_rooms = ft_lstnew(tab[0], ft_strlen(tab[0]));
				else
					ft_lstadd(&room->linked_rooms, ft_lstnew(tab[0], ft_strlen(tab[0])));
			}
			tmp = tmp->next;
		}
	}
	ft_printf("OK");
}

t_lem_in				*ft_get_data()
{
	t_lem_in	*data;

	data = (t_lem_in *)malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->nb_ants = ft_get_nb_ants();
	data->nb_rooms = 0;
	data->start_room = NULL;
	data->end_room = NULL;
	data->rooms = ft_get_rooms(data);
	ft_get_link_rooms(data);
	debug_data(data);
	return (data);
}