/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:36:12 by akozin            #+#    #+#             */
/*   Updated: 2024/07/18 13:38:44 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_sp(t_data *data, char **s)
{
	int	elem_c;

	elem_c = str_arr_counter(s);
	if (elem_c == 5 && ft_strncmp(s[4], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c == 4 && !ft_strncmp(s[3], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c != 4 && elem_c != 5)
		return ((void)(data->error = PARAM_N_ERR));
	data->objs[data->c_obj].type = SP;
	data->objs[data->c_obj].origin = parse_origin(data, s[1]);
	data->objs[data->c_obj].diameter = parse_rational_positive(data, s[2]);
	data->objs[data->c_obj].color = parse_rgb(data, s[3]);
	data->c_obj++;
}
