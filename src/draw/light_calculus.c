/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus.c                                   :+:      :+:    :+:   */
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

/*
 * 1. get the point in space where the collision has occured
 * by doing camera.origin + f * col.r_dist
 * 2. get object. if plane, normal = plane normal
 * if sphere, normal = calc sphere normal or whatever
 * cylinder = you guessed it
 * 3. iterate thru every availabe light. if there is a ray between the light
 * and the col point without collisions, then take the light into account.
 * 4. for those lights, the intensity = cosine of the angle between the normal
 * and the light direction (light-col vector), calculates with the dot product
 * if light-col = 0, we should prob give max intensity type of deal
 *
 * let's suppose a light intensity scaling model with distance that goes like:
 *
 *                            1
 * -------------------------------------------------------------- = real int
 *                    1.01 - intensity [ranges from 0.01 to 1.01]
 * (distance to light)
 *
 * this would mean that the more intense the light, the more gradual
 * the fall-off.
 *
 * or you know what could be better actually?
 *
 * intensity calc:
 * base intensity * falloff func
 * falloff = 1 / const ^ (distance + 1)
 * all that and multiply instead of add. since it's simple diffuse, no
 * we can't make a green ball white with all the light (sorry, blender's
 * principled bsdf)
 *
 * in case of amb, 1 = normal illum, 0 = none (no crazy stuff)
 */
/*
 * some logic logic logic:
 * 1. if we're inside a sphere (or a cylinder for that matter)
 * 1.1. if the light is inside the sphere:
 * do normal lighting, calculating intersections etc, but the sphere
 * normals are (-1)'d.
 * 1.2. if the light is outside of the sphere:
 * disregard it completely.
 * 2. if we're outside of a sphere
 * 2.1. if the light is inside the sphere:
 * disregard it completely.
 * 2.2. if the light is outside of the sphere:
 * do normal lighting, calculating intersections etc.
 */
t_rgb	light_calc(t_data *data, t_col col, t_vec3 f)
{
	t_rgb	ret;
	t_ray	r_light;
	int		j;
	double	dist_l;
	double	scale_factor;

	j = 0;
	light_calc_init(data, &col, f, &ret);
	while (j < data->light_n)
	{
		if (ignore_light(data, &j))
			continue ;
		r_light.f = vec_sub(col.p, data->lights[j].origin);
		normalize(&(r_light.f));
		r_light.o = col.p;
		if (light_blocked(data, r_light, &j, &dist_l))
			continue ;
		if (data->objs[col.obj_ind].type == SP)
			scale_factor = data->lights[j].power / pow(FALLOFF, dist_l) \
							* sc_fac_calc_sp(data, col, r_light);
		else if (data->objs[col.obj_ind].type == PL)
			scale_factor = data->lights[j].power / pow(FALLOFF, dist_l + 2);
		ret = super_mix(ret, data->lights[j++].color, scale_factor);
	}
	return (ret);
}
