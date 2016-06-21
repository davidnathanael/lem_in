/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 10:29:35 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/08 10:29:36 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool		ft_is_comment(char *str)
{
	if (str && *str == '#' && *(str + 1) != '#')
		return (TRUE);
	return (FALSE);
}

t_bool		ft_is_valid_command(char *str)
{
	if (ft_strcmp("##start", str) == 0 || ft_strcmp("##end", str) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool		ft_is_room(char *str)
{
	char	**tab;
	t_bool	is_room;

	tab = ft_strsplit(str, ' ');
	is_room = TRUE;
	if (ft_tablen(tab) != 3)
		is_room = FALSE;
	else
	{
		if ((!ft_is_number(tab[1])) || (!ft_is_number(tab[2])))
		is_room = FALSE;
	}
	ft_free_str_tab(tab);
	return (is_room);
}

t_bool		ft_is_available_room(char *str, t_list *rooms)
{
	t_room		*room;

	room = ft_get_room_by_name(str, rooms);
	if (room->is_occupied)
		return (FALSE);
	return (TRUE);
}
