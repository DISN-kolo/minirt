/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus_internal_funcs.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:48:52 by akozin            #+#    #+#             */
/*   Updated: 2024/07/25 15:41:12 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/* 
 * used only for the global light calc? maybe it's ok to use in
 * the light ignore check? XXX
 */
int	is_c_in_sp(t_obj sp, t_cam cam)
{
	if (distance(cam.origin, sp.origin) < sp.diameter / 2.)
		return (1);
	return (0);
}

double	sc_fac_calc_sp(t_data *data, t_col col, t_ray r_light)
{
	double	sc_fac_mult;

	sc_fac_mult = dot_prod(
			sphere_n(data->objs[col.obj_ind], col.p), r_light.f);
	if (is_c_in_sp(data->objs[col.obj_ind], data->cam))
		sc_fac_mult *= -1;
	return (sc_fac_mult);
}

int	light_blocked(t_data *data, t_ray r_light, int *j, double *dist_l)
{
	t_col	l_block;
	int		i;

	l_block.obj_ind = -1;
	l_block.r_dist = INFINITY;
	i = 0;
	while (i < data->obj_n)
		l_block = check_os_from_int_p(r_light, data, i++, l_block);
	*dist_l = distance(data->curr_c.p, data->lights[*j].origin);
	if (*dist_l > l_block.r_dist)
	{
		(*j)++;
		return (1);
	}
	return (0);
}

void	light_calc_init(t_data *data, t_col *col, t_vec3 f, t_rgb *ret)
{
	col->p = vec_add(data->cam.origin, vec_scale(f, col->r_dist));
	data->curr_c = *col;
	*ret = data->objs[col->obj_ind].color;
	*ret = rgb_mult(*ret, rgb_scale(data->amb.color, data->amb.power));
}
