/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f < fcosta-f@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:25:59 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/18 20:49:30 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * o - ray origin
 * d - ray direction
 * pp - plane origin
 * n - normal vector of the plane
 *
 * if n and d are perpendicular, i.e., the ray is parallel to the plane,
 * then obviously no intersection is possible
 *
 * the x solution comes from equating these two P's (random points):
 * 1. a point P along the ray:            P = o + d * x
 * 2. a way to write the plane equation: (P - p) . n = 0
 *
 * 1 is easily explained as start + direction * advancement
 * 2 is explained as "the dot product = 0 => the vectors are perpendicular",
 * therefore what is perpendicular to a plane's perpendicular is lying in
 * the plane itself.
 *
 * so, equating these two P's, we get a place where they meet - thus, an
 * intersection (this is the general logic with all the following shapes too)
 *
 * (o + d*x - p) . n = 0
 * o . n + d*x . n - p . n = 0
 * d . n *x = (p-o) . n
 * x = (p-o) . n / d . n
 */
double	splane_ray(t_vec3 o, t_vec3 d, t_vec3 pp, t_vec3 n)
{
	double	x;
	double	den;

	den = dot_prod(n, d);
	if (den == 0)
		return (INFINITY);
	x = (dot_prod(n, vec_sub(pp, o))) / den;
	if (x > 0)
		return (x);
	else
		return (INFINITY);
}
