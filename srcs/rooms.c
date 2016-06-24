/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 11:49:16 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/24 12:16:11 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_handle_command(char *command, t_lem_in *data)
{
	t_room	*room;
	char	*buf;

	buf = NULL;
	room = NULL;
	if (ft_strcmp("##start", command) == 0 || ft_strcmp("##end", command) == 0)
	{
		get_next_line(0, &buf);
		ft_lstappend(&data->to_print, ft_lstnew(buf, ft_strlen(buf) + 1));
		room = ft_extract_room(buf, data);
		if (ft_strcmp("##start", command) == 0)
		{
			ft_lstadd(&data->rooms, ft_lstnew((t_room *)room, sizeof(*room)));
			data->start_room = data->rooms->content;
		}
		else if (ft_strcmp("##end", command) == 0)
		{
			ft_lstadd(&data->rooms, ft_lstnew((t_room *)room, sizeof(*room)));
			data->end_room = data->rooms->content;
		}
	}
	else
		return ;
}

t_room		*ft_extract_room(char *infos, t_lem_in *data)
{
	char	**tab;
	t_room	*room;

	tab = ft_strsplit(infos, ' ');
	room = (t_room *)malloc(sizeof(*room));
	room->name = ft_strdup(tab[0]);
	room->x = ft_atoi(tab[1]);
	room->y = ft_atoi(tab[2]);
	room->weight = INITIAL_WEIGHT;
	room->is_occupied = FALSE;
	room->linked_rooms = NULL;
	data->nb_rooms++;
	ft_free_str_tab(tab);
	return (room);
}

t_room		*ft_get_room_by_name(char *name, t_list *rooms)
{
	t_list	*tmp;
	t_room	*room;

	tmp = rooms;
	while (tmp)
	{
		room = tmp->content;
		if (ft_strcmp(room->name, name) == 0)
			return (room);
		tmp = tmp->next;
	}
	return (NULL);
}

t_bool		ft_create_room(char *infos, t_lem_in *data)
{
	t_room		*room;

	room = ft_extract_room(infos, data);
	if (!ft_check_coor(data->rooms, room))
		return (FALSE);
	if (!data->rooms)
		data->rooms = ft_lstnew((t_room *)room, sizeof(*room));
	else
		ft_lstadd(&data->rooms, ft_lstnew((t_room *)room, sizeof(*room)));
	return (TRUE);
}
