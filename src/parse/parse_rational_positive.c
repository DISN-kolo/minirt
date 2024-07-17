/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rational_positive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:21:27 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 16:47:23 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	parse_rational_positive(t_data *data, char *s)
{
	int		past_the_point;
	double	res;

	past_the_point = 0;
	res = 0.0;
	while (*s && *s != '\n')
	{
		if (*s == '-')
			return (data->error = DOUBLE_ERR, -0.0);
		if (ft_isdigit(*s))
			res = atod_res_add_logic(&past_the_point, res, *s);
		else if (*s == '.' && !past_the_point)
			past_the_point = 1;
		else
			return (data->error = DOUBLE_ERR, -0.0);
		s++;
	}
	return (res);
}
