/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 13:49:45 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/03 13:52:10 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_get_available_room(t_room *actual_room, t_lem_in *data)
{
	t_list	*linked_rooms;
	t_room	*room;

	linked_rooms = actual_room->linked_rooms;
	room = NULL;
	while (linked_rooms)
	{
		room = ft_get_room_by_name(linked_rooms->content, data->rooms);
		if (!room->is_occupied && room->weight < actual_room->weight)
		{
			actual_room->is_occupied = FALSE;
			room->is_occupied = TRUE;
			return (room);
		}
		linked_rooms = linked_rooms->next;
	}
	//ft_printf("RETURN NULL ROOM\n");
	return (room);
}

void			ft_move(t_list *list_ant, t_lem_in *data)
{
	t_ant		*ant;
	t_room		*room;

	ant = list_ant->content;
	room = ft_get_available_room(ant->actual_room, data);
	if (!room)
		return ;
	ft_printf("ant nb {red}%d{eoc} moved from room {red}%s{eoc} to room {red}%s{eoc}\n", ant->nb, ant->actual_room->name, room->name);
	ant->actual_room = room;
	if (room == data->end_room)
	{
		ft_printf("ant {red}%d{eoc} arrived\n", ant->nb);
		data->nb_arrived_ants++;
	}
}

static void		lem_in(t_lem_in *data)
{
	t_list	*ants;

	ants = data->ants;
	while (ants)
	{
		ft_move(ants, data);
		ants = ants->next;
	}
	ft_check_possible_creation(data);
	ft_printf("lem_in() out\n\n");
}

int				main(void)
{
	t_lem_in	*data;

	data = ft_get_data();
	if (data == NULL)
	{
		ft_printf("ERROR\n");
		return (-1);
	}
	debug_data(data);
	while (data->nb_created_ants < data->nb_ants)
		lem_in(data);
	return (0);
}
