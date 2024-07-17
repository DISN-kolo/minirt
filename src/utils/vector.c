/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:51:01 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/17 12:41:07 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double vec_len(t_vec3 vec)
{
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
	v.x = v.x * f;
	v.y = v.y * f;
	v.z = v.z * f;
	return (v);
}

//puede devolver el vector
void normalize(t_vec3 *v)
{
	double norm;

	norm = 1/vec_len(*v);
	v->x *= norm;
	v->y *= norm;
	v->z *= norm;
}
