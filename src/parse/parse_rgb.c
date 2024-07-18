/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:33:29 by akozin            #+#    #+#             */
/*   Updated: 2024/07/18 13:39:34 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * why the negative values?
 * well, you never know :)
 */
static int	rgb_failcheck(t_rgb i)
{
	if (i.r > 255 || i.r < 0 || i.g > 255 || i.g < 0 || i.b > 255 || i.b < 0)
		return (1);
	return (0);
}

static void	internal_rgb_parser(t_data *data, int col, t_rgb *res, char c)
{
	if (col == 0)
	{
		res->r = res->r * 10 + (int)(c - '0');
		if (res->r > 255)
			return ((void)(data->error = RGB_ERR));
	}
	else if (col == 1)
	{
		res->g = res->g * 10 + (int)(c - '0');
		if (res->g > 255)
			return ((void)(data->error = RGB_ERR));
	}
	else if (col == 2)
	{
		res->b = res->b * 10 + (int)(c - '0');
		if (res->b > 255)
			return ((void)(data->error = RGB_ERR));
	}
	else
		return ((void)(data->error = RGB_ERR));
}

static void	inside_the_rgb_while(t_data *data, t_rgb *res, char *s, int *col)
{
	if (ft_isdigit(*s))
	{
		internal_rgb_parser(data, (*col), res, *s);
		if (data->error != NULL_ERR)
			return ;
	}
	else if (*s == ',')
	{
		(*col)++;
		if (!*(s + 1) || !ft_isdigit(*(s + 1)))
			return ((void)(data->error = RGB_ERR));
	}
	else
		return ((void)(data->error = RGB_ERR));
}

/*
 * col:   0 1 2
 *        r g b
 */
t_rgb	parse_rgb(t_data *data, char *s)
{
	t_rgb	res;
	int		col;

	res = rgb_init();
	col = 0;
	while (*s && *s != '\n')
	{
		inside_the_rgb_while(data, &res, s, &col);
		s++;
	}
	if (data->error != NULL_ERR)
		return (res);
	if (rgb_failcheck(res))
		return (data->error = RGB_ERR, res);
	return (res);
}
