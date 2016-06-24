/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 16:15:02 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/23 16:15:04 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		ft_print_move(t_room *from, t_room *to, int nb, t_bool verbose)
{
	if (verbose)
	{
		ft_printf("{bold}Ant number {green}%d{default} moved from ", nb);
		ft_printf("{red}%s", from->name);
		ft_printf("{default} to {red}%s{eoc}", to->name);
	}
	else
		ft_printf("{bold}L{green}%d{default}-{red}%s{eoc} ", nb, to->name);
}

static void	ft_print_room(t_room *room, t_lem_in *data)
{
	t_list	*linked;

	linked = room->linked_rooms;
	ft_printf("Name :  {red}%s{eoc} | Weight : {red}%d{eoc} | Links : ",
				room->name, room->weight);
	while (linked)
	{
		ft_printf("{red}%s{eoc} | ", linked->content);
		linked = linked->next;
	}
	if (room == data->start_room)
		ft_printf("{bold}{green}=> START ROOM{eoc}");
	else if (room == data->end_room)
		ft_printf("{bold}{green}=> END ROOM{eoc}");
	ft_putchar('\n');
}

void		ft_print_data(t_lem_in *data)
{
	t_list	*tmp;

	tmp = data->rooms;
	ft_printf("-------------- DATA --------------\n\n");
	ft_printf("NUMBER OF ANTS : {green}{bold}%u{eoc}\n", data->nb_ants);
	ft_printf("NUMBER OF ROOMS : {green}{bold}%u{eoc}\n\n", data->nb_rooms);
	ft_printf("-------------- ROOMS -------------\n\n");
	while (tmp)
	{
		ft_print_room(tmp->content, data);
		tmp = tmp->next;
	}
	ft_putchar('\n');
}
