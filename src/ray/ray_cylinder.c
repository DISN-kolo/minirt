/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f < fcosta-f@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:15:59 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/20 23:49:28 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static double	caps_intersection(t_cam cam, const t_obj obj)
{
	double	d1;
	double	d2;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	c2;

	c2 = vec_add(obj.origin, prod_esc(obj.normal, obj.height)); //center of the top cap:
	d1 = plane_ray(cam.origin, cam.normal, obj.origin, obj.normal);
	d2 = plane_ray	(cam.origin, cam.normal, c2, obj.normal);
	if (d1 < INFINITY || d2 < INFINITY)
	{
		p1 = vec_add(cam.origin, prod_esc(cam.normal, d1));
		p2 = vec_add(cam.origin, prod_esc(cam.normal, d2));
		if ((d1 < INFINITY && distance(p1, obj.origin) <= obj.diameter/2) && (d2 < INFINITY && distance(p2, c2) <= obj.diameter/2)) {
			if (d1 < d2)
				return (d1);
			return (d2);
		}
		else if (d1 < INFINITY && distance(p1, obj.origin) <= obj.diameter/2)
			return (d1);
		else if (d2 < INFINITY && distance(p2, c2) <= obj.diameter/2)
			return (d2);
	}
	return (INFINITY);
}

static int		solve_quadratic(double result[2], t_vec3 o, t_vec3 d, t_obj *obj)
{
	double	q[3];
	t_vec3 v;
	t_vec3 w;

	v = prod_esc(obj->normal, dot_prod(d, obj->normal)); // It shows how much of d is in the same direction as the cylinder's axis.
	v = vec_sub(d, v); //vec_sub v from d leaves us with the component of d that is perpendicular to the cylinder's axis.
	w = prod_esc(obj->normal, dot_prod(obj->normal, vec_sub(o, obj->origin)));
	w = vec_sub(vec_sub(o, obj->origin), w);
	q[0] = dot_prod(v, v);
	q[1] = 2 * dot_prod(v, w);
	q[2] = dot_prod(w, w) - pow(obj->diameter/2, 2);
	result[0] = (-q[1] + sqrt(pow(q[1], 2) - 4 * q[0] * q[2])) / (2 * q[0]);
	result[1] = (-q[1] - sqrt(pow(q[1], 2) - 4 * q[0] * q[2])) / (2 * q[0]);
	if ((!result[0] && !result[1]) || (result[0] < EPSILON && result[1] < EPSILON)) //If the solutions are NaN, it means the quadratic equation did not have real solutions, so the ray does not intersect the cylinder. If both solutions are very small (less than EPSILON), it means the intersection points are very close to the origin or behind the ray's starting point, which might be considered invalid for the intersection.
		return (0);
	return (1);
}

static void		calc_correct_inters(double x2[2], const t_obj obj, double dist1, double dist2)
{
	double	x;

	if ((dist1 >= 0 && dist1 <= obj.height && x2[0] > EPSILON) && 
        (dist2 >= 0 && dist2 <= obj.height && x2[1] > EPSILON)) //both valid
    {
        if (x2[0] < x2[1]) //closer inters
            x = x2[0];
        else
            x = x2[1];
    }
	else if (dist1 >= 0 && dist1 <= obj.height && x2[0] > EPSILON) //one valid
		x = x2[0];
	else
		x = x2[1];
	x2[0] = x;
}

static double	body_inters(t_cam cam, t_obj obj)
{
	double	x2[2];

	if (!solve_quadratic(x2, cam.origin, cam.normal, &obj))
		return (INFINITY);
	double d1 = dot_prod(obj.normal, vec_sub(prod_esc(cam.normal, x2[0]), vec_sub(obj.origin, cam.origin)));
	double d2 = dot_prod(obj.normal, vec_sub(prod_esc(cam.normal, x2[1]), vec_sub(obj.origin, cam.origin)));
	if (!((d1 >= 0 && d1 <= obj.height && x2[0] > EPSILON) || (d2 >= 0 && d2 <= obj.height && x2[0] > EPSILON)))
		return (INFINITY);
	calc_correct_inters(x2, obj, d1, d2);
	return (x2[0]);
}

double	cylinder_intersection(const t_cam cam, const t_obj obj) //done
{
	double	dbody;
	double	dcaps;

	dbody = body_inters(cam, obj);
	dcaps = caps_intersection(cam, obj);
	if (dbody < INFINITY || dcaps < INFINITY)
	{
		if (dbody < dcaps) //que est'a m'as cerca
			return (dbody);
		return (dcaps);
	}
	return (INFINITY);
}

t_vec3 point_to_line(t_vec3 A, t_vec3 B, t_vec3 P)
{
	t_vec3 AP, AB;
	double ab2, ap_ab, t;
	
	AP = vec_sub(P, A);
	AB = vec_sub(B, A);
	ab2 = dot_prod(AB, AB);
	ap_ab = dot_prod(AP, AB);
	t = ap_ab / ab2; //unitario, 0 es A, 1 es B
	if (t < 0.0)
		t = 0.0;
	else if (t > 1.0)
		t = 1.0;
	return (vec_add(A, prod_esc(AB, t)));
	//Adds the scaled vector to point A, giving us the point along the line segment AB that is closest to P.
}
