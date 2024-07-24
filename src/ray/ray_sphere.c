/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:31:30 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/24 14:10:45 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vec3	sphere_n(t_obj sp, t_vec3 p)
{
	t_vec3	res;

	res = vec_sub(sp.origin, p);
	if (vec_len(res) < sp.diameter / 2.)
	{
		//printf("tee hee! someone scaled the normal\n");
		vec_scale(res, -1.);
	}
	normalize(&res);
	return (res);
}

static void	solve_quadratic(double result[2], t_vec3 o, t_vec3 d, t_obj *obj)
{
	t_vec3	oc;
	double	disc;
	double	q[3];

	oc = vec_sub(obj->origin, o); //from ray origin to sphere center
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

// literally the og func but gets the further intersection.
double	sphere_far_result(t_vec3 o, t_vec3 d, t_obj *obj)
{
	double	pfar;
	double	x[2];

	pfar = INFINITY;
	solve_quadratic(x, o, d, obj);
	if (x[0] > EPSILON && !isinf(x[0]))
		pfar = x[0];
	if (x[1] > EPSILON && !isinf(x[1])) {
		if (x[1] > x[0])
			pfar = x[1];
	}
	return (pfar);
}

double	sphere_intersection(t_vec3 o, t_vec3 d, t_obj *obj)
{
	double	pnear;
	double	x[2];

	pnear = INFINITY;
	solve_quadratic(x, o, d, obj);
	if (x[0] > EPSILON && !isinf(x[0])) //epsilon to avoid precision errors self-intersection...
		pnear = x[0];
	if (x[1] > EPSILON && !isinf(x[1])) {
		if (x[1] < x[0])
			pnear = x[1];
	}
	return (pnear);
	//creo que si hubiera otra textura habría que hacer más comprobaciones pero ahora mismo da igual
}
