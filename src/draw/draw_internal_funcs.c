/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_internal_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:29:50 by akozin            #+#    #+#             */
/*   Updated: 2024/07/25 14:41:09 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vec3	find_f(t_data *data, int px, int py, t_ur ur)
{
	t_vec3	f;

	f = vec_add(data->cam.normal, vec_scale(ur.r,
				WIN_X / WIN_Y * tan(
					data->cam.fov / 2.) * (2 * px / WIN_X - 1)));
	f = vec_add(f, vec_scale(ur.u,
				tan(data->cam.fov / 2.) * (2 * py / WIN_Y - 1)));
	normalize(&f);
	return (f);
}

t_ur	set_up_right(t_data *data, t_ur ur)
{
	ur.u.x = 0;
	ur.u.y = -1;
	ur.u.z = 0;
	ur.r = cross_prod(data->cam.normal, ur.u);
	normalize(&(ur.r));
	ur.u = cross_prod(data->cam.normal, ur.r);
	normalize(&(ur.u));
	ur.u = vect_inv(ur.u);
	return (ur);
}
