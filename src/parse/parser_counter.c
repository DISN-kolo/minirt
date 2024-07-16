/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_counter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:59:36 by akozin            #+#    #+#             */
/*   Updated: 2024/07/16 13:08:50 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	count_object_in_line(t_data *data, char *s)
{
	while (*s && *s != '\n' && *s == ' ')
		s++;
	if (!*s || *s == '\n')
		return ((void)(data->error = TYPE_ERR));
	if (!ft_strncmp(s, "A ", 2))
	{
		data->amb_n += 1;
		if (data->amb_n > 1)
			return ((void)(data->error = TOO_MUCH_ERR));
		return ;
	}
	else if (!ft_strncmp(s, "C ", 2))
	{
		data->cam_n += 1;
		if (data->cam_n > 1)
			return ((void)(data->error = TOO_MUCH_ERR));
		return ;
	}
	else if (!ft_strncmp(s, "L ", 2))
		return ((void)(data->light_n += 1));
	else if (!ft_strncmp(s, "sp ", 3) || !ft_strncmp(s, "pl ", 3)
		|| !ft_strncmp(s, "cy ", 3))
		return ((void)(data->obj_n += 1));
	return ((void)(data->error = TYPE_ERR));
}

void	parser_counter(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "\n", 2) || data->error != NULL_ERR)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		count_object_in_line(data, line);
		if (data->error != NULL_ERR)
			continue ;
		free(line);
		line = get_next_line(fd);
	}
}
