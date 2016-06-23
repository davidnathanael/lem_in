/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adompe <adompe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 15:44:23 by adompe            #+#    #+#             */
/*   Updated: 2016/06/20 15:44:26 by adompe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool		ft_check_coor(t_list *rooms, t_room *room)
{
	t_list		*tmp;
	t_room		*tmp_room;

	tmp = rooms;
	while (tmp)
	{
		tmp_room = tmp->content;
		if (tmp_room->x == room->x && tmp_room->y == room->y)
			return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

t_bool		ft_check_start_end(t_lem_in *data)
{
	if (data->end_room == NULL || data->start_room == NULL)
		return (FALSE);
	return (TRUE);
}

t_bool		ft_check_link(t_room *start)
{
	if (start->weight == -1)
		return (FALSE);
	return (TRUE);
}
