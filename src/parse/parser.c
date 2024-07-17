/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:52:58 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 16:38:25 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	decide_and_read(t_data *data, char **s)
{
	if (!ft_strncmp(s[0], "A", 2))
		parse_amb(data, s);
	else if (!ft_strncmp(s[0], "C", 2))
		parse_cam(data, s);
	else if (!ft_strncmp(s[0], "L", 2))
		parse_lig(data, s);
	else if (!ft_strncmp(s[0], "sp", 3))
		parse_sp(data, s); // TODO
//	else if (!ft_strncmp(s[0], "pl", 3))
//		parse_pl(data, s); // TODO
//	else if (!ft_strncmp(s[0], "cy", 3))
//		parse_cy(data, s); // TODO
//	return ((void)(data->error = TYPE_ERR));
}
//  ^^^^^^<--- just in case. lol

/*
 * copying the EOL check from parser counter "just in case"
 * i.e. i'm too lazy to be mathematically sure we won't encounter a fail here
 */
static void	parse_line(t_data *data, char *s)
{
	char	**parsed_line;

	while (*s && *s != '\n' && *s == ' ')
		s++;
	if (!*s || *s == '\n')
		return ((void)(data->error = TYPE_ERR));
	parsed_line = ft_split(s, ' ');
	if (!parsed_line)
		return ((void)(data->error = MALLOC_ERR));
	decide_and_read(data, parsed_line);
	free_str_arr(&parsed_line);
}

void	parser(t_data *data, int fd)
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
		parse_line(data, line);
		if (data->error != NULL_ERR)
			continue ;
		free(line);
		line = get_next_line(fd);
	}
}
