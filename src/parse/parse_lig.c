/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:51:20 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 17:00:46 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_rgb	rgb_white(void)
{
	t_rgb	ret;

	ret.r = 255;
	ret.g = 255;
	ret.b = 255;
	return (ret);
}

/*
 * remember! the color is not an obligatory field
 */
void	parse_lig(t_data *data, char **s)
{
	int	elem_c;

	elem_c = str_arr_counter(s);
	if (elem_c == 5 && ft_strncmp(s[4], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c == 3 && !ft_strncmp(s[2], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c != 3 && elem_c != 4 && elem_c != 5)
		return ((void)(data->error = PARAM_N_ERR));
	data->lights[data->c_light].origin = parse_origin(data, s[1]);
	data->lights[data->c_light].power = parse_power(data, s[2]);
	if (elem_c == 3 || (elem_c == 4 && !ft_strncmp(s[3], "\n", 2)))
		data->lights[data->c_light].color = rgb_white();
	else
		data->lights[data->c_light].color = parse_rgb(data, s[3]);
	data->c_light++;
}
/*
 * an example of printing for debug:
 */
/*
	printf("l params:\n\
\torigin: %f %f %f\n\
\tcol: %3d %3d %3d\n\
\tpower: %f\n\
\tnumber: %d\n",
		data->lights[data->c_light].origin.x,
		data->lights[data->c_light].origin.y,
		data->lights[data->c_light].origin.z,
		data->lights[data->c_light].color.r,
		data->lights[data->c_light].color.g,
		data->lights[data->c_light].color.b,
		data->lights[data->c_light].power,
		data->c_light); // XXX
 */
