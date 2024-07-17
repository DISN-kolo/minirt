/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:09:54 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 15:44:39 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_cam(t_data *data, char **s)
{
	int	elem_c;

	elem_c = str_arr_counter(s);
	if (elem_c == 5 && ft_strncmp(s[4], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c == 4 && !ft_strncmp(s[3], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c != 4 && elem_c != 5)
		return ((void)(data->error = PARAM_N_ERR));
	data->cam.origin = parse_origin(data, s[1]);
	data->cam.normal = parse_normal(data, s[2]);
	data->cam.fov = parse_fov(data, s[3]);
	printf("cam params:\n\
\torigin: %f %f %f\n\
\tnormal: %f %f %f\n\
\tfov: %d\n",
		data->cam.origin.x,
		data->cam.origin.y,
		data->cam.origin.z,
		data->cam.normal.x,
		data->cam.normal.y,
		data->cam.normal.z,
		data->cam.fov); // XXX
}
