/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:08:02 by akozin            #+#    #+#             */
/*   Updated: 2024/07/25 16:05:29 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vec3	parse_normal(t_data *data, char *s)
{
	t_vec3	res;

	res = parse_origin(data, s);
	if (data->error != NULL_ERR)
		return (res);
	normalize(&res);
	if (vec_len(res) < EPSILON)
		return (data->error = NORMAL_ERR, res);
	return (res);
}
