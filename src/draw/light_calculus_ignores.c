/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus_ignores.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:52 by akozin            #+#    #+#             */
/*   Updated: 2024/07/25 15:45:08 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * sphere only. must make a selector TODO
 * shall have an inside-cylinder formula too.....
 */
int	ignore_light_sp(t_data *data, int oi, int j)
{
	if (distance(data->cam.origin,
			data->objs[oi].origin) < data->objs[oi].diameter / 2.)
	{
		if (distance(data->lights[j].origin,
				data->objs[oi].origin) > data->objs[oi].diameter / 2.)
			return (1);
	}
	else
	{
		if (distance(data->lights[j].origin,
				data->objs[oi].origin) < data->objs[oi].diameter / 2.)
			return (1);
	}
	return (0);
}

int	ignore_light_pl(t_data *data, int oi, int j)
{
	int	sign_a;
	int	sign_b;

	sign_a = (dot_prod(vec_sub(data->objs[oi].origin, data->cam.origin),
				data->objs[oi].normal) > 0);
	sign_b = (dot_prod(vec_sub(data->objs[oi].origin, data->lights[j].origin),
				data->objs[oi].normal) > 0);
	return (sign_a != sign_b);
}

int	ignore_light(t_data *data, int *j)
{
	int	oi;

	oi = 0;
	while (oi < data->obj_n)
	{
		if (data->objs[oi].type == SP)
		{
			if (ignore_light_sp(data, oi, *j))
				return ((*j)++, 1);
		}
		else if (data->objs[oi].type == PL)
		{
			if (ignore_light_pl(data, oi, *j))
				return ((*j)++, 1);
		}
		oi++;
	}
	return (0); // TODO cylinder
}
