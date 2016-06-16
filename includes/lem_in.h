/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 13:50:29 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/16 16:58:22 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"

# define INITIAL_WEIGHT	-1

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				weight;
	t_bool			is_occupied;
	t_list			*linked_rooms;
}					t_room;

typedef struct		s_lem_in
{
	unsigned int	nb_ants;
	unsigned int	nb_rooms;
	t_list			*rooms;
	t_room			*start_room;
	t_room			*end_room;
	char			*buf;
}					t_lem_in;

t_lem_in			*ft_get_data();
void				ft_handle_command(char *command, t_lem_in *data);
t_room				*ft_extract_room(char *infos, t_lem_in *data);
t_room				*ft_get_room_by_name(char *name, t_list *rooms);

t_bool				ft_is_comment(char *str);
t_bool				ft_is_valid_command(char *str);
t_bool				ft_is_room(char *str);
void				ft_get_link_rooms(t_lem_in *data);

void				debug_data(t_lem_in *data);

#endif
