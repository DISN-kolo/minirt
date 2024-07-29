/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f < fcosta-f@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:25:59 by fcosta-f          #+#    #+#             */
/*   Updated: 2024/07/20 22:44:28 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double			plane_ray(t_vec3 o, t_vec3 d, t_vec3 pp, t_vec3 n)
{ //o origen rayo, d direccion rayo, pp punto en el plano, n vector normal plano
	double	x;
	double  den;

	den = dot_prod(n, d);
	if (den == 0) //ray paralelo al plano no interseccion
		return (INFINITY);
	x = (dot_prod(n, vec_sub(pp, o))) / den;
    if (x > 0)
        return (x);
    else //una intersección negativa indicaría que el punto de intersección entre el rayo y el plano se encuentra detrás del origen del rayo.
        return (INFINITY);
}