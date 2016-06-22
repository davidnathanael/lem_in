/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 10:49:04 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/08 10:49:05 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void debug_data(t_lem_in *data)
{
	ft_printf("-------------- DATA --------------\n\n");


	ft_printf("NUMBER OF ANTS : {green}{bold}%u{eoc}\n", data->nb_ants);
	ft_printf("NUMBER OF ROOMS : {green}{bold}%u{eoc}\n\n", data->nb_rooms);

	ft_printf("-------------- ROOMS -------------\n\n");

	t_list	*tmp = data->rooms;
	t_room	*room = tmp->content;
	t_list	*tmp_link = NULL;

	while (tmp)
	{
		room = tmp->content;
		ft_printf("NAME :  {red}%s -> %p{eoc} | weight : %d | linked to : ", room->name, room, room->weight);
		tmp_link = room->linked_rooms;
		while (tmp_link)
		{
			ft_printf("{red}%s{eoc} | ", tmp_link->content);
			tmp_link = tmp_link->next;
		}
		ft_putchar('\n');

		tmp = tmp->next;
	}
	room = data->start_room;
	ft_printf("START : {red}%s -> %p{eoc} -> x : {green}%d{eoc} | y : {green}%d{eoc}\n",
	room->name, room, room->x, room->y);
	room = data->end_room;
	ft_printf("END :  {red}%s -> %p{eoc} -> x : {green}%d{eoc} | y : {green}%d{eoc}\n",
	room->name, room, room->x, room->y);
}


void debug_ants(t_list *ants)
{
	t_list	*tmp = ants;
	t_ant	*ant = tmp->content;

	while (tmp)
	{
		ant = tmp->content;
		printf("ant nb : %d | actual room : %s\n", ant->nb, ant->current_room->name);
		tmp = tmp->next;
	}
}
