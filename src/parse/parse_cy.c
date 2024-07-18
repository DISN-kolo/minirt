/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:48:24 by akozin            #+#    #+#             */
/*   Updated: 2024/07/18 14:59:55 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_cy(t_data *data, char **s)
{
	int	elem_c;

	elem_c = str_arr_counter(s);
	if (elem_c == 7 && ft_strncmp(s[6], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c == 6 && !ft_strncmp(s[5], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c != 6 && elem_c != 7)
		return ((void)(data->error = PARAM_N_ERR));
	data->objs[data->c_obj].type = CY;
	data->objs[data->c_obj].origin = parse_origin(data, s[1]);
	data->objs[data->c_obj].normal = parse_normal(data, s[2]);
	data->objs[data->c_obj].diameter = parse_rational_positive(data, s[3]);
	data->objs[data->c_obj].height = parse_rational_positive(data, s[4]);
	data->objs[data->c_obj].color = parse_rgb(data, s[5]);
	data->c_obj++;
}
