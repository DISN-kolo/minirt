/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_internal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:07:20 by akozin            #+#    #+#             */
/*   Updated: 2024/07/31 12:10:48 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ci_cond_one(double d1, t_vec3 p1, t_obj obj)
{
	return (d1 < INFINITY && distance(p1, obj.origin) <= obj.diameter / 2);
}

int	ci_cond_two(double d2, t_vec3 p2, t_vec3 c2, t_obj obj)
{
	return (d2 < INFINITY && distance(p2, c2) <= obj.diameter / 2);
}

/*
 * adds the scaled vector to point a, giving us the point along
 * the line segment ab that is closest to p.
 */
t_vec3	point_to_line(t_vec3 a, t_vec3 b, t_vec3 p)
{
	t_vec3	ap;
	t_vec3	ab;
	double	ab2;
	double	ap_ab;
	double	t;

	ap = vec_sub(p, a);
	ab = vec_sub(b, a);
	ab2 = dot_prod(ab, ab);
	ap_ab = dot_prod(ap, ab);
	t = ap_ab / ab2;
	if (t < 0.0)
		t = 0.0;
	else if (t > 1.0)
		t = 1.0;
	return (vec_add(a, vec_scale(ab, t)));
}
