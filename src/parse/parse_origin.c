/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_origin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:26:17 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 15:01:07 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

double	parse_float(t_data *data, char **s)
{
	int		past_the_point;
	double	res;
	int		sign;

	past_the_point = 0;
	res = 0.0;
	sign = 1 - (**s == '-') * 2;
	*s += (**s == '-');
	if (!ft_isdigit(**s) && **s != '.')
		return (data->error = DOUBLE_ERR, -0.0);
	while (**s && **s != ',' && **s != ' ')
	{
		if (ft_isdigit(**s))
			res = atod_res_add_logic(&past_the_point, res, **s);
		else if (**s == '.' && !past_the_point)
			past_the_point = 1;
		else
			return (data->error = DOUBLE_ERR, -0.0);
		(*s)++;
	}
	return (res * sign);
}

static void	intern_vec3_fill(t_data *data, int ax, char **s, t_vec3 *res)
{
	if (ax == 0)
		res->x = parse_float(data, s);
	else if (ax == 1)
		res->y = parse_float(data, s);
	else if (ax == 2)
		res->z = parse_float(data, s);
	else
		return ((void)(data->error = ORIGIN_ERR));
}

t_vec3	vec3_init(void)
{
	t_vec3	res;

	res.x = 0;
	res.y = 0;
	res.z = 0;
	return (res);
}

t_vec3	parse_origin(t_data *data, char *s)
{
	t_vec3	res;
	int		ax;

	res = vec3_init();
	ax = 0;
	while (*s && *s != ' ')
	{
		if (*s == ',')
		{
			if (ax == 2 || *(s + 1) == ',')
				return (data->error = ORIGIN_ERR, res);
			ax++;
			s++;
		}
		else
			intern_vec3_fill(data, ax, &s, &res);
	}
	if (ax != 2)
		return (data->error = ORIGIN_ERR, res);
	return (res);
}
