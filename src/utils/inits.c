/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:12:55 by akozin            #+#    #+#             */
/*   Updated: 2024/07/16 13:23:24 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	data_init(t_data *data)
{
	data->light_n = 0;
	data->obj_n = 0;
	data->cam_n = 0;
	data->amb_n = 0;
	data->error = NULL_ERR;
	data->lights = NULL;
	data->objs = NULL;
}

void	allocate_stuff(t_data *data)
{
	data->lights = malloc(sizeof (t_light) * (data->light_n + 1));
	if (!data->lights)
		return ((void)(data->error = MALLOC_ERR));
	data->objs = malloc(sizeof (t_obj) * (data->obj_n + 1));
	if (!data->objs)
		return ((void)(data->error = MALLOC_ERR));
}
