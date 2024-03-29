/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 13:50:29 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/24 12:14:55 by ddela-cr         ###   ########.fr       */
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

typedef struct		s_ant
{
	int				nb;
	t_room			*current_room;
}					t_ant;

typedef struct		s_lem_in
{
	t_list			*ants;
	unsigned int	nb_ants;
	unsigned int	nb_arrived_ants;
	unsigned int	nb_created_ants;
	unsigned int	nb_rooms;
	t_list			*rooms;
	t_room			*start_room;
	t_room			*end_room;
	char			*buf;
	t_list			*to_print;
	t_bool			verbose;
	t_bool			color;
}					t_lem_in;

t_lem_in			*ft_get_data(int ac, char **av);
void				ft_move(t_list *list_ant, t_lem_in *data);
void				ft_handle_command(char *command, t_lem_in *data);
t_bool				ft_create_room(char *infos, t_lem_in *data);
t_room				*ft_extract_room(char *infos, t_lem_in *data);
t_room				*ft_get_room_by_name(char *name, t_list *rooms);

t_room				*ft_get_available_room(t_room *current_room,
											t_lem_in *data);

t_ant				*ft_create_ant(t_lem_in *data);
t_bool				ft_check_possible_creation(t_lem_in *data);
t_bool				ft_can_go_to_room(t_room *current, t_room *dest);

t_bool				ft_is_comment(char *str);
t_bool				ft_is_command(char *str);
t_bool				ft_is_room(char *str);
void				ft_get_link_rooms(t_lem_in *data);
t_bool				ft_is_available_room(char *str, t_list *rooms);

t_bool				ft_check_coor(t_list *rooms, t_room *room);
t_bool				ft_check_start_end(t_lem_in *data);

void				ft_print_move(t_room *from, t_room *to, int nb,
								t_lem_in *data);
void				ft_print_data(t_lem_in *data);
#endif
