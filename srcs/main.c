/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 13:49:45 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/08/09 14:01:06 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room			*ft_get_available_room(t_room *current_room, t_lem_in *data)
{
	t_list	*linked_rooms;
	t_room	*room;

	linked_rooms = current_room->linked_rooms;
	room = NULL;
	if (current_room == data->end_room)
		return (NULL);
	while (linked_rooms)
	{
		room = ft_get_room_by_name(linked_rooms->content, data->rooms);
		if (ft_can_go_to_room(current_room, room))
			return (room);
		linked_rooms = linked_rooms->next;
	}
	return (room);
}

void			ft_move(t_list *list_ant, t_lem_in *data)
{
	t_ant		*ant;
	t_room		*room;

	ant = list_ant->content;
	room = ft_get_available_room(ant->current_room, data);
	if (!room || !ft_can_go_to_room(ant->current_room, room))
		return ;
	ft_print_move(ant->current_room, room, ant->nb, data);
	ant->current_room->is_occupied = FALSE;
	room->is_occupied = (room == data->end_room) ? FALSE : TRUE;
	ant->current_room = room;
	if (room == data->end_room)
	{
		if (data->verbose)
			ft_printf("{bold}{red} -> ARRIVED!{eoc}\n");
		else
			ft_putchar(' ');
		data->nb_arrived_ants++;
	}
	else
		(data->verbose) ? ft_putchar('\n') : ft_putchar(' ');
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
	while (ft_check_possible_creation(data))
		;
	ft_putchar('\n');
}

int				main(int ac, char **av)
{
	t_lem_in	*data;

	data = ft_get_data(ac, av);
	if (data == NULL)
	{
		ft_printf("ERROR\n");
		return (-1);
	}
	while (data->to_print)
	{
		ft_printf("%s\n", data->to_print->content);
		data->to_print = data->to_print->next;
	}
	ft_putchar('\n');
	if (data->verbose)
		ft_print_data(data);
	while (data->nb_arrived_ants < data->nb_ants)
		lem_in(data);
	free(data);
	return (0);
}
