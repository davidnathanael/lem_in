/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddela-cr <ddela-cr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 22:12:58 by ddela-cr          #+#    #+#             */
/*   Updated: 2016/06/06 16:59:42 by ddela-cr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include "libft.h"

int			ft_append(int const fd, char **overflow, int *ret)
{
	char			*buf;
	char			*tmp;

	buf = ft_strnew(GNL_BUFF_SIZE);
	tmp = NULL;
	if ((*ret = read(fd, buf, GNL_BUFF_SIZE)) == GNL_ERROR)
		return (GNL_ERROR);
	if (*overflow == '\0')
		*overflow = ft_strnew(0);
	buf[*ret] = '\0';
	tmp = *overflow;
	*overflow = ft_strjoin(*overflow, buf);
	free(tmp);
	free(buf);
	return (0);
}

int			ft_store_line(char **overflow, char **line)
{
	char			*str;

	if ((str = ft_strchr(*overflow, '\n')))
	{
		*str = '\0';
		*line = ft_strdup(*overflow);
		ft_memmove(*overflow, str + 1, ft_strlen(str + 1) + 1);
		return (GNL_READ);
	}
	return (GNL_END);
}

void		ft_check_fd(t_gnl **list, t_gnl **overflow, int fd)
{
	t_gnl		*new;

	*overflow = *list;
	while (*overflow)
	{
		if ((*overflow)->fd == fd)
			break ;
		*overflow = (*overflow)->next;
	}
	if (!*overflow)
	{
		new = (t_gnl *)malloc(sizeof(t_gnl));
		new->fd = fd;
		new->overflow = ft_strnew(0);
		new->next = *list;
		*list = new;
		*overflow = *list;
	}
}

int			get_next_line(int const fd, char **line)
{
	static t_gnl		*list;
	t_gnl				*tmp;
	int					ret;

	if (fd < 0 || !line)
		return (-1);
	ft_check_fd(&list, &tmp, fd);
	ret = GNL_BUFF_SIZE;
	while (ret > 0 || ft_strlen(tmp->overflow))
	{
		if ((ft_store_line(&(tmp->overflow), line)) == GNL_READ)
			return (GNL_READ);
		if (ft_append(fd, &(tmp->overflow), &ret) == GNL_ERROR)
			return (GNL_ERROR);
		if (ret == 0 && ft_strlen(tmp->overflow))
		{
			*line = ft_strdup(tmp->overflow);
			ft_bzero(tmp->overflow, ft_strlen(tmp->overflow));
			return (GNL_READ);
		}
	}
	free(tmp->overflow);
	tmp->overflow = NULL;
	return (GNL_END);
}
