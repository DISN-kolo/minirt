/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:08:02 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 15:12:11 by akozin           ###   ########.fr       */
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
	return (res);
}
