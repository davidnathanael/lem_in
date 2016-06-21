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

t_room	*ft_get_available_room(t_room *actual_room)
{
	t_list	*linked_rooms;
	t_room	*room;

	linked_rooms = actual_room->linked_rooms;
	room = NULL;
	while (linked_rooms)
	{
		room = linked_rooms->content;
		if (!room->is_occupied && room->weight < actual_room->weight)
			return (room);
		linked_rooms = linked_rooms->next;
	}
	return (room);
}

void			ft_move(t_ant *ant, t_lem_in *data)
{
	t_room		*room;

	room = ft_get_available_room(ant->actual_room);
	if (!room)
		return ;
	printf("%d\n", ant->nb);
	// printf("%d moved %s -> %s\n", ant->nb, ant->actual_room->name, room->name);
	ant->actual_room = room;
	if (room == data->end_room)
		data->nb_arrived_ants++;
}

static void		lem_in(t_lem_in *data)
{
	t_list	*ants;

	ants = data->ants;
	while (ants)
	{
		ft_move(ants->content, data);
		ants = ants->next;
	}
	ft_check_possible_creation(data);
	ft_printf("lem_in() out\n");
}

int				main(void)
{
	t_lem_in	*data;

	data = ft_get_data();
	while (data->nb_created_ants < data->nb_ants)
		lem_in(data);
	return (0);
}
