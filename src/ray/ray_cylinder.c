/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f < fcosta-f@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:15:59 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/31 12:11:11 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * c2 is the center of the top cap
 */
static double	caps_intersection(t_ray cam, const t_obj obj)
{
	double	d1;
	double	d2;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	c2;

	c2 = vec_add(obj.origin, vec_scale(obj.normal, obj.height));
	d1 = plane_ray(cam.o, cam.f, obj.origin, obj.normal);
	d2 = plane_ray(cam.o, cam.f, c2, obj.normal);
	if (d1 < INFINITY || d2 < INFINITY)
	{
		p1 = vec_add(cam.o, vec_scale(cam.f, d1));
		p2 = vec_add(cam.o, vec_scale(cam.f, d2));
		if (ci_cond_one(d1, p1, obj) && ci_cond_two(d2, p2, c2, obj))
		{
			if (d1 < d2)
				return (d1);
			return (d2);
		}
		else if (d1 < INFINITY && distance(p1, obj.origin) <= obj.diameter / 2)
			return (d1);
		else if (d2 < INFINITY && distance(p2, c2) <= obj.diameter / 2)
			return (d2);
	}
	return (INFINITY);
}

/*
 * at first,
 * vector v shows how much of d is in the same direction
 * as the cylinder's axis.
 * but then,
 * vec_sub v from d leaves us with the component of d
 * that is perpendicular to the cylinder's axis.
 *
 * the if condition:
 * If the solutions are NaN, it means the quadratic equation
 * did not have real solutions, so the ray does not intersect the cylinder.
 * If both solutions are very small (less than EPSILON),
 * it means the intersection points are very close to the origin or behind
 * the ray's starting point, which might be considered invalid
 * for the intersection.
 */
static int	solve_quadratic(double result[2], t_vec3 o, t_vec3 d, t_obj *obj)
{
	double	q[3];
	t_vec3	v;
	t_vec3	w;

	v = vec_scale(obj->normal, dot_prod(d, obj->normal));
	v = vec_sub(v, d);
	w = vec_scale(obj->normal, dot_prod(obj->normal, vec_sub(o, obj->origin)));
	w = vec_sub(vec_sub(o, obj->origin), w);
	q[0] = dot_prod(v, v);
	q[1] = 2 * dot_prod(v, w);
	q[2] = dot_prod(w, w) - pow(obj->diameter / 2, 2);
	result[0] = (-q[1] + sqrt(pow(q[1], 2) - 4 * q[0] * q[2])) / (2 * q[0]);
	result[1] = (-q[1] - sqrt(pow(q[1], 2) - 4 * q[0] * q[2])) / (2 * q[0]);
	if ((!result[0] && !result[1])
		|| (result[0] < EPSILON && result[1] < EPSILON))
		return (0);
	return (1);
}

/*
 * the fist if checks for the validity of BOTH the intersections
 *
 * the inside if determines the closer one
 *
 * the else if determines if only a single of them is valid
 */
static void	calc_correct_inters(double x2[2], const t_obj obj,
		double dist1, double dist2)
{
	double	x;

	if ((dist1 >= 0 && dist1 <= obj.height && x2[0] > EPSILON)
		&& (dist2 >= 0 && dist2 <= obj.height && x2[1] > EPSILON))
	{
		if (x2[0] < x2[1])
			x = x2[0];
		else
			x = x2[1];
	}
	else if (dist1 >= 0 && dist1 <= obj.height && x2[0] > EPSILON)
		x = x2[0];
	else
		x = x2[1];
	x2[0] = x;
}

static double	body_inters(t_ray cam, t_obj obj)
{
	double	x2[2];
	double	d1;
	double	d2;

	if (!solve_quadratic(x2, cam.o, cam.f, &obj))
		return (INFINITY);
	d1 = dot_prod(obj.normal, vec_sub(vec_sub(cam.o, obj.origin),
				vec_scale(cam.f, x2[0])));
	d2 = dot_prod(obj.normal, vec_sub(vec_sub(cam.o, obj.origin),
				vec_scale(cam.f, x2[1])));
	if (!((d1 >= 0 && d1 <= obj.height && x2[0] > EPSILON)
			|| (d2 >= 0 && d2 <= obj.height && x2[0] > EPSILON)))
		return (INFINITY);
	calc_correct_inters(x2, obj, d1, d2);
	return (x2[0]);
}

/*
 * after calculating both possible itnersections, we pick the closest
 */
double	cylinder_intersection(int *b, const t_ray cam, const t_obj obj)
{
	double	dbody;
	double	dcaps;

	dbody = body_inters(cam, obj);
	dcaps = caps_intersection(cam, obj);
	if (dbody < INFINITY || dcaps < INFINITY)
	{
		if (dbody < dcaps)
			return (*b = 1, dbody);
		return (*b = 0, dcaps);
	}
	return (INFINITY);
}
