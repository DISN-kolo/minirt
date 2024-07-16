/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:51:01 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/16 17:18:51 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double vec_len(t_vec3 vec) {
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	t_vec3 v;

	v.x = b.x - a.x;
	v.y = b.y - a.y;
	v.z = b.z - a.z;
	return (v);
}

t_vec3	vect_add(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = b.x + a.x;
	v.y = b.y + a.y;
	v.z = b.z + a.z;
	return (v);
}

t_vec3	prod_esc(t_vec3 v, double f)
{
	t_vec3	v;

	v.x = v.x * f;
	v.y = v.y * f;
	v.z = v.z * f;
	return (v);
}

void normalize(t_vec3 *v) { //puede devolver el vector
	double norm;
	
	norm = 1/vec_len(*v);
	v->x *= norm;
	v->y *= norm;
	v->z *= norm;
}

double	dot_prod(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	cross_prod(t_vec3 u, t_vec3 v)
{
	t_vec3 result;

	result.x = u.y * v.z - u.z * v.y;
	result.y = u.z * v.x - u.x * v.z;
	result.z = u.x * v.y - u.y * v.x;
	return (result);
}

double	distance(t_vec3 a, t_vec3 b)
{
	double	x;
	double	y;
	double	z;

	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
	x = pow(x, 2);
	y = pow(y, 2);
	z = pow(z, 2);
	return (sqrt(x + y + z));
}

t_vec3	vect_inv(t_vec3 v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

void printVector(t_vec3 v) {
	printf("vect: %f, %f, %f\n", v.x, v.y, v.z);
}