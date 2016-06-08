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
	while (tmp)
	{
		room = tmp->content;
		ft_printf("NAME :  {red}%s{eoc} -> x : {green}%d{eoc} | y : {green}%d{eoc}\n",
		room->name, room->x, room->y);
		tmp = tmp->next;
	}
	room = data->start_room;
	ft_printf("START : {red}%s{eoc} -> x : {green}%d{eoc} | y : {green}%d{eoc}\n",
	room->name, room->x, room->y);
	room = data->end_room;
	ft_printf("END :  {red}%s{eoc} -> x : {green}%d{eoc} | y : {green}%d{eoc}\n",
	room->name, room->x, room->y);
}
