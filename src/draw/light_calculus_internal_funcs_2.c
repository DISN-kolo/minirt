/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculus_internal_funcs_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:17:43 by akozin            #+#    #+#             */
/*   Updated: 2024/07/31 18:20:07 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	light_dist_calc(t_data *data, int j, int oi)
{
	double	light_dist;
	t_vec3	light_dist_v;

	light_dist_v = vec_sub(data->lights[j].origin, data->objs[oi].origin);
	light_dist = vec_len(vec_sub(vec_scale(data->objs[oi].normal,
					dot_prod(light_dist_v, data->objs[oi].normal)),
				light_dist_v));
	return (light_dist);
}
