/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 11:49:16 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/08 11:49:18 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_handle_command(char *command, t_lem_in *data)
{
	t_room	*room;
	char	*buf;

	buf = NULL;
	room = NULL;
	get_next_line(0, &buf);
	room = ft_extract_room(buf, data);
	if (ft_strcmp("##start", command) == 0)
	{
		data->start_room = room;
		ft_lstadd(&data->rooms, ft_lstnew((t_room *)room, sizeof(*room)));
	}
	else if (ft_strcmp("##end", command) == 0)
	{
		data->end_room = room;
		ft_lstadd(&data->rooms, ft_lstnew((t_room *)room, sizeof(*room)));
	}
}

t_room	*ft_extract_room(char *infos, t_lem_in *data)
{
	char	**tab;
	t_room	*room;

	tab = ft_strsplit(infos, ' ');
	room = (t_room *)malloc(sizeof(*room));
	room->name = ft_strdup(tab[0]);
	room->x = ft_atoi(tab[1]);
	room->y = ft_atoi(tab[2]);
	room->weight = 0;
	room->is_occupied = FALSE;
	room->linked_rooms = NULL;
	data->nb_rooms++;
	ft_free_str_tab(tab);
	return (room);
}
