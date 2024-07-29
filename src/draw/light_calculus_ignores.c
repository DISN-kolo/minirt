/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus_ignores.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:52 by akozin            #+#    #+#             */
/*   Updated: 2024/07/29 18:29:05 by akozin           ###   ########.fr       */
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

int	internal_ignore_light_cy(t_data *data, int oi, int j)
{
	t_vec3	cam_dist_v;
	t_vec3	light_dist_v;
	double	cam_dist;
	double	light_dist;

	cam_dist_v = vec_sub(data->cam.origin, data->objs[oi].origin);
	cam_dist = vec_len(vec_sub(vec_scale(data->objs[oi].normal,
					dot_prod(cam_dist_v, data->objs[oi].normal)),
				cam_dist_v));
	light_dist_v = vec_sub(data->lights[j].origin, data->objs[oi].origin);
	light_dist = vec_len(vec_sub(vec_scale(data->objs[oi].normal,
					dot_prod(light_dist_v, data->objs[oi].normal)),
				light_dist_v));
	if (cam_dist < data->objs[oi].diameter / 2.)
	{
		if (light_dist > data->objs[oi].diameter / 2.)
			return (1);
	}
	else
	{
		if (light_dist < data->objs[oi].diameter / 2.)
			return (1);
	}
	return (0);
}

/*
 * a - sign of cam and plane 1
 * b - sign of light and plane 1
 * c - sign of cam and plane 2
 * d - sign of light and plane 2
 */
int	ignore_light_cy(t_data *data, int oi, int j)
{
	int		sign_a;
	int		sign_b;

	sign_a = (dot_prod(vec_sub(data->objs[oi].origin, data->cam.origin),
				data->objs[oi].normal) > 0);
	sign_b = (dot_prod(vec_sub(data->objs[oi].origin, data->lights[j].origin),
				data->objs[oi].normal) > 0);
	if (sign_a == 0 && sign_b == 0)
		return (0);
	sign_a = (dot_prod(vec_sub(vec_add(data->objs[oi].origin,
						vec_scale(data->objs[oi].normal,
							data->objs[oi].height)), data->cam.origin),
				data->objs[oi].normal) > 0);
	sign_b = (dot_prod(vec_sub(vec_add(data->objs[oi].origin,
						vec_scale(data->objs[oi].normal,
							data->objs[oi].height)), data->lights[j].origin),
				data->objs[oi].normal) > 0);
	if (sign_a > 0 && sign_b > 0)
		return (0);
	return (internal_ignore_light_cy(data, oi, j));
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
		else if (data->objs[oi].type == CY)
		{
			if (ignore_light_cy(data, oi, *j))
				return ((*j)++, 1);
		}
		oi++;
	}
	return (0);
}
