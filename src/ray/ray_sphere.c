/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:31:30 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/22 14:22:59 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void		solve_quadratic(double result[2], t_vec3 o, t_vec3 d, t_obj *obj)
{
	t_vec3	oc;
	double	disc;
	double	q[3];

	oc = vec_sub(o, obj->origin); //from ray origin to sphere center
	q[0] = dot_prod(d, d);
	q[1] = 2 * dot_prod(d, oc);
	q[2] = dot_prod(oc, oc) - obj->diameter/2.0 * obj->diameter/2.0;
	disc = q[1] * q[1] - (4 * q[0] * q[2]); //discriminant to know if there are real solutions eq 2o grado de toda la vida
	if (disc < 0)
	{
		result[0] = INFINITY;
		result[1] = INFINITY;
		return ;
	}
	result[0] = (-q[1] + sqrt(disc)) / (2 * q[0]);
	result[1] = (-q[1] - sqrt(disc)) / (2 * q[0]);
}

double	sphere_intersection(t_vec3 o, t_vec3 d, t_obj *obj)
{
	double	pnear;
	double	x[2];

	pnear = INFINITY;
	solve_quadratic(x, o, d, obj);
	if (x[0] > EPSILON && x[0] < INFINITY) //epsilon to avoid precision errors self-intersection...
		pnear = x[0];
	if (x[1] > EPSILON && x[1] < INFINITY) {
		if (x[1] < x[0])
			pnear = x[1];
	}
	return (pnear);
	//creo que si hubiera otra textura habría que hacer más comprobaciones pero ahora mismo da igual
}
