/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 11:23:17 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/21 11:23:19 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ant	*ft_create_ant(t_lem_in *data)
{
	t_ant	*ant;

	ant = (t_ant *)malloc(sizeof(*ant));
	ant->nb = ++(data->nb_created_ants);
	ant->current_room = data->start_room;
	return (ant);
}

t_bool	ft_check_possible_creation(t_lem_in *data)
{
	t_room		*room;
	t_list		*new;
	t_ant		*ant;

	ant = NULL;
	new = NULL;
	room = ft_get_available_room(data->start_room, data);
	if (!room || room->is_occupied || data->nb_created_ants >= data->nb_ants)
		return (FALSE);
	ant = ft_create_ant(data);
	new = ft_lstnew(ant, sizeof(*ant));
	ft_lstappend(&(data->ants), new);
	ft_move(new, data);
	return (TRUE);
}

t_bool	ft_can_go_to_room(t_room *current, t_room *dest)
{
	if (dest->is_occupied || dest->weight >= current->weight)
		return (FALSE);
	return (TRUE);
}
