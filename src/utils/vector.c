/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f <fcosta-f@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:51:01 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/17 15:10:58 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	vec_len(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = b.x - a.x;
	v.y = b.y - a.y;
	v.z = b.z - a.z;
	return (v);
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = b.x + a.x;
	v.y = b.y + a.y;
	v.z = b.z + a.z;
	return (v);
}

t_vec3	vec_scale(t_vec3 v, double f)
{
	t_vec3	w;

	w.x = v.x * f;
	w.y = v.y * f;
	w.z = v.z * f;
	return (w);
}

//puede devolver el vector
void	normalize(t_vec3 *v)
{
	double	norm;
	double	vlen;

	vlen = vec_len(*v);
	if (vlen == 0.)
		return ;
	norm = 1 / vlen;
	v->x *= norm;
	v->y *= norm;
	v->z *= norm;
}
