/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:53:52 by akozin            #+#    #+#             */
/*   Updated: 2024/07/22 17:32:34 by akozin           ###   ########.fr       */
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
	//printf("obj #%d, collision point: ", col.obj_ind);
	//print_vector(col_p);
	ret = data->objs[col.obj_ind].color;
	ret = rgb_mult(ret, rgb_scale(data->amb.color, data->amb.power));
	while (j < data->light_n)
	{
		f_light = vec_sub(data->lights[j].origin, col_p);
		normalize(&f_light);
		l_block.obj_ind = -1;
		l_block.r_dist = INFINITY;
		i = 0;
		while (i < data->obj_n)
			l_block = check_objs_internal(f, data, i++, l_block);
		double dist_l = distance(col_p, data->lights[j].origin);
		printf("epic collision with distance: %f\n", dist_l);
		printf("starting ")
		if (l_block.obj_ind == -1 || isinf(l_block.r_dist)
				|| l_block.r_dist > dist_l || l_block.r_dist < 2. * EPSILON)
		{
			//XXX
			double scale_factor = data->lights[j].power / pow(FALLOFF, dist_l);
			t_rgb perceived_light = rgb_scale(data->lights[j].color, scale_factor);
			ret = rgb_mult(ret, perceived_light);
			printf("AND HIS OVERWHELMING INTENSITY!\n");
		}
		else
		{
		//	printf("ind: %d\nisinf: %d\ndist: %f\nneeded: %f\n", l_block.obj_ind, isinf(l_block.r_dist), l_block.r_dist, distance(col_p, data->lights[j].origin));
		//	if (l_block.obj_ind != -1)
		//		printf("obj: %d\n", data->objs[l_block.obj_ind].type);
		}
		j++;
	}
//	printf("r:  g:  b:\n %3d %3d %3d\n", data->amb.color.r, data->amb.color.g, data->amb.color.b);
//	t_rgb newc = rgb_scale(data->amb.color, data->amb.power);
//	printf("r:  g:  b:\n %3d %3d %3d\n", newc.r, newc.g, newc.b);
	return (ret);
}
