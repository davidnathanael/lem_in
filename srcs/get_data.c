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
	t_room	*room;

	buf = NULL;
	room = NULL;
	data->rooms = NULL;
	while (get_next_line(0, &buf))
	{
		//ft_printf("BUF : %s\n", buf);
		if (ft_is_valid_command(buf))
			ft_handle_command(buf, data);
		else if (ft_is_room(buf))
		{
			room = ft_extract_room(buf, data);
			if (!data->rooms)
				data->rooms = ft_lstnew((t_room *)room, sizeof(*room));
			else
				ft_lstadd(&data->rooms, ft_lstnew((t_room *)room, sizeof(*room)));
		}
		else if (ft_is_comment(buf))
			;
		else
		{
			data->buf = ft_strdup(buf);
			break;
		}
	}
	return (data->rooms);
}

static unsigned int		ft_get_nb_ants()
{
	char	*buf;
	int		nb_ants;

	buf = NULL;
	nb_ants = 0;
	while (get_next_line(0, &buf) && ft_is_comment(buf))
		;
	if ((nb_ants = ft_atoi(buf)) <= 0)
	{
		ft_printf("Error : Incorrect number of ants.\n");
		exit(0);
	}
	return (nb_ants);
}

t_lem_in				*ft_get_data()
{
	t_lem_in	*data;

	data = (t_lem_in *)malloc(sizeof(*data));
	if (!data)
		return (NULL);
	data->nb_ants = ft_get_nb_ants();
	data->nb_rooms = 0;
	data->start_room = NULL;
	data->end_room = NULL;
	data->rooms = ft_get_rooms(data);

	debug_data(data);
	return NULL;
}
