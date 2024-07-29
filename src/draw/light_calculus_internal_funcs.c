/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus_internal_funcs.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:48:52 by akozin            #+#    #+#             */
/*   Updated: 2024/07/29 18:23:54 by akozin           ###   ########.fr       */
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

int	is_c_in_cy(t_obj cy, t_cam cam)
{
	t_vec3	cam_dist_v;
	double	cam_dist;
	int		sign_a;
	int		sign_c;

	sign_a = (dot_prod(vec_sub(cy.origin, cam.origin),
				cy.normal) > 0);
	sign_c = (dot_prod(vec_sub(vec_add(cy.origin,
						vec_scale(cy.normal,
							cy.height)), cam.origin),
				cy.normal) > 0);
	cam_dist_v = vec_sub(cam.origin, cy.origin);
	cam_dist = vec_len(vec_sub(vec_scale(cy.normal,
					dot_prod(cam_dist_v, cy.normal)), cam_dist_v));
	if (sign_a > 0 && sign_c == 0 && cam_dist < cy.diameter / 2.)
		return (1);
	return (0);
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
