/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus_sf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:58:49 by akozin            #+#    #+#             */
/*   Updated: 2024/07/31 18:15:49 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	sc_fac_calc_sp(t_data *data, t_col col, t_ray r_light)
{
	double	sc_fac_mult;

	sc_fac_mult = dot_prod(
			sphere_n(data->objs[col.obj_ind], col.p), r_light.f);
	if (is_c_in_sp(data->objs[col.obj_ind], data->cam))
		sc_fac_mult *= -1;
	return (sc_fac_mult);
}

t_vec3	cylinder_n(t_obj cy, t_vec3 p)
{
	t_vec3	op;
	t_vec3	interm;
	t_vec3	res;

	op = vec_sub(cy.origin, p);
	interm = cross_prod(op, cy.normal);
	res = cross_prod(cy.normal, interm);
	normalize(&res);
	return (res);
}

double	sc_fac_calc_cy(t_data *data, t_col col, t_ray r_light)
{
	double	sc_fac_mult;

	if (data->objs[col.obj_ind].cy_b == 1)
	{
		sc_fac_mult = dot_prod(
				cylinder_n(data->objs[col.obj_ind], col.p), r_light.f);
		if (is_c_in_cy(data->objs[col.obj_ind], data->cam))
		{
			print_vector(cylinder_n(data->objs[col.obj_ind], col.p));
			sc_fac_mult *= -1;
		}
	}
	else if (data->objs[col.obj_ind].cy_b == 0)
		return (1 / pow(FALLOFF, 2));
	else
	{
		ft_putstr_fd("something is wrong\n", 2);
		return (100);
	}
	return (sc_fac_mult);
}
