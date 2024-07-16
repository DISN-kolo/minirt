/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:35:05 by akozin            #+#    #+#             */
/*   Updated: 2024/07/16 16:22:35 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_amb(t_data *data, char **s)
{
	int	elem_c;

	elem_c = str_arr_counter(s);
	if (elem_c == 4 && ft_strncmp(s[3], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c == 3 && !ft_strncmp(s[2], "\n", 2))
		return ((void)(data->error = PARAM_N_ERR));
	else if (elem_c != 3 && elem_c != 4)
		return ((void)(data->error = PARAM_N_ERR));
	data->amb.power = parse_power(data, s[1]);
	// data->amb.color = parse_rgb(data, s[2]); // TODO
	printf("amb color intensity: %f\n", data->amb.power); // XXX
}
