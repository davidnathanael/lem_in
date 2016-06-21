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
	ant->actual_room = data->start_room;
	printf("created ant nb %d\n", ant->nb);
	return (ant);
}

void	ft_check_possible_creation(t_lem_in *data)
{
	t_room		*room;
	t_ant		*ant;

	room = ft_get_available_room(data->start_room, data);
	ant = NULL;
	if (!room || data->nb_created_ants >= data->nb_ants)
		return ;
	ant = ft_create_ant(data);
	ft_lstappend(&(data->ants), ft_lstnew(ant, sizeof(*ant)));
	ft_move(ant, data);
}
