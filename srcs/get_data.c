/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 16:40:27 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/06 16:40:28 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list			*ft_get_rooms(t_lem_in *data)
{
	char	*buf;

	buf = NULL;
	data->rooms = NULL;
	while (get_next_line(0, &buf))
	{
		ft_lstappend(&data->to_print, ft_lstnew(buf, ft_strlen(buf) + 1));
		if (ft_is_command(buf))
			ft_handle_command(buf, data);
		else if (ft_is_room(buf))
		{
			if (!ft_create_room(buf, data))
				return (NULL);
		}
		else if (ft_is_comment(buf))
			;
		else
		{
			data->buf = ft_strdup(buf);
			break ;
		}
	}
	return (data->rooms);
}

static unsigned int		ft_get_nb_ants(t_lem_in *data)
{
	char	*buf;
	int		nb_ants;

	buf = NULL;
	nb_ants = 0;
	while (get_next_line(0, &buf) && ft_is_comment(buf))
		ft_lstappend(&data->to_print, ft_lstnew(buf, ft_strlen(buf) + 1));
	ft_lstappend(&data->to_print, ft_lstnew(buf, ft_strlen(buf) + 1));
	if ((nb_ants = ft_atoi(buf)) <= 0)
	{
		ft_printf("Error : Incorrect number of ants.\n");
		exit(0);
	}
	return (nb_ants);
}

void					ft_set_weight(t_room *room, int weight, t_list *rooms)
{
	t_list	*linked_rooms;
	t_room	*tmp_room;

	linked_rooms = room->linked_rooms;
	room->weight = weight;
	while (linked_rooms)
	{
		tmp_room = ft_get_room_by_name(linked_rooms->content, rooms);
		if (tmp_room->weight == INITIAL_WEIGHT || tmp_room->weight > weight)
			ft_set_weight(tmp_room, weight + 1, rooms);
		linked_rooms = linked_rooms->next;
	}
}

static void				ft_set_weights(t_lem_in *data)
{
	int		weight;
	t_room	*start;

	weight = 0;
	start = data->end_room;
	ft_set_weight(start, weight, data->rooms);
}

t_lem_in				*ft_get_data(int ac, char **av)
{
	t_lem_in	*data;

	data = (t_lem_in *)malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->verbose = ((ac > 1) && ft_strcmp("-v", av[1]) == 0) ? TRUE : FALSE;
	data->ants = NULL;
	data->to_print = NULL;
	data->nb_ants = ft_get_nb_ants(data);
	data->nb_arrived_ants = 0;
	data->nb_created_ants = 0;
	data->nb_rooms = 0;
	data->start_room = NULL;
	data->end_room = NULL;
	data->rooms = ft_get_rooms(data);
	if (!ft_check_start_end(data))
		return (NULL);
	ft_get_link_rooms(data);
	ft_set_weights(data);
	if (data->start_room->weight == -1)
		return (NULL);
	return (data);
}
