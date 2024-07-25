/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:31:30 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/25 14:27:42 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * since the inside of the sphere stuff is managed too, the -1 scale is very
 * important for these situations :)
 */
t_vec3	sphere_n(t_obj sp, t_vec3 p)
{
	t_vec3	res;

	res = vec_sub(sp.origin, p);
	if (vec_len(res) < sp.diameter / 2.)
		vec_scale(res, -1.);
	normalize(&res);
	return (res);
}

/*
 * derived from the sphere's equation and the ray's equation having common
 * points/solutions. therefore this func is just solving this eq.
 * more info at
 *
 * hugi.scene.org/
 *  online/hugi24/coding graphics chris dragan raytracing shapes.htm
 *
 * 2 results = 2 intersections
 * 1 result  = you guessed it
 * 0 results = missed
 */
static void	solve_quadratic(double result[2], t_vec3 o, t_vec3 d, t_obj *obj)
{
	t_vec3	oc;
	double	disc;
	double	q[3];

	oc = vec_sub(obj->origin, o);
	q[0] = dot_prod(d, d);
	q[1] = 2 * dot_prod(d, oc);
	q[2] = dot_prod(oc, oc) - obj->diameter / 2.0 * obj->diameter / 2.0;
	disc = q[1] * q[1] - (4 * q[0] * q[2]);
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
	if (x[0] > EPSILON && !isinf(x[0]))
		pnear = x[0];
	if (x[1] > EPSILON && !isinf(x[1]))
	{
		if (x[1] < x[0])
			pnear = x[1];
	}
	return (pnear);
}
