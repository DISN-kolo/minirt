/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:52 by akozin            #+#    #+#             */
/*   Updated: 2024/07/23 17:03:08 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
t_rgb	light_calc(t_data *data, t_col col, t_vec3 f)
{
	t_vec3	col_p;
	t_rgb	ret;
	t_vec3	f_light;
	t_col	l_block;
	int		j;
	int		i;
	
	j = 0;
	col_p = vec_add(data->cam.origin, vec_scale(f, col.r_dist));
//	printf("obj #%d, collision point: ", col.obj_ind);
//	print_vector(col_p);
	ret = data->objs[col.obj_ind].color;
	ret = rgb_mult(ret, rgb_scale(data->amb.color, data->amb.power));
	while (j < data->light_n)
	{
		f_light = vec_sub(col_p, data->lights[j].origin);
		normalize(&f_light);
		l_block.obj_ind = -1;
		l_block.r_dist = INFINITY;
		i = 0;
		while (i < data->obj_n)
			l_block = check_objs_internal(f_light, data, i++, l_block);
		double dist_l = distance(col_p, data->lights[j].origin);
		if (l_block.obj_ind == -1 || isinf(l_block.r_dist)
				|| l_block.r_dist > dist_l || l_block.r_dist < 2. * EPSILON)
		{
			if (data->objs[col.obj_ind].type == SP)
			{
				double scale_factor = data->lights[j].power / pow(FALLOFF, dist_l);
				scale_factor *= dot_prod(sphere_n(data->objs[col.obj_ind], col_p), f_light) / (vec_len(sphere_n(data->objs[col.obj_ind], col_p)) * vec_len(f_light));
				if (data->objs[col.obj_ind].diameter / 2. > distance(data->cam.origin, data->objs[col.obj_ind].origin))
				{
					if (data->objs[col.obj_ind].diameter / 2. > distance(data->lights[j].origin, data->objs[col.obj_ind].origin))
					{
						scale_factor *= -1;
						t_rgb perceived_light = rgb_scale(data->lights[j].color, scale_factor);
						ret = rgb_add(ret, perceived_light);
					}
				}
				else
				{
					t_rgb perceived_light = rgb_scale(data->lights[j].color, scale_factor);
					ret = rgb_add(ret, perceived_light);
				}
			}
			else
			{
//				printf("AND HIS OVERWHELMING INTENSITY!\n");
				//XXX
				double scale_factor = data->lights[j].power / pow(FALLOFF, dist_l);
//				printf("j = %d, sf = %f\n", j, scale_factor);
				t_rgb perceived_light = rgb_scale(data->lights[j].color, scale_factor);
				ret = rgb_add(ret, perceived_light);
			}
		}
//		else
//			printf("dist: %f\nneeded: %f\n", l_block.r_dist, dist_l);
		j++;
	}
//	printf("r:  g:  b:\n %3d %3d %3d\n", data->amb.color.r, data->amb.color.g, data->amb.color.b);
//	t_rgb newc = rgb_scale(data->amb.color, data->amb.power);
//	printf("r:  g:  b:\n %3d %3d %3d\n", newc.r, newc.g, newc.b);
	return (ret);
}
