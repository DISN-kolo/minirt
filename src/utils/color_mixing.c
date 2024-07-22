/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mixing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:42:12 by akozin            #+#    #+#             */
/*   Updated: 2024/07/22 16:24:48 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_rgb	rgb_add(t_rgb c1, t_rgb c2)
{
	t_rgb	res;

	res.r = c1.r + c2.r;
	res.g = c1.g + c2.g;
	res.b = c1.b + c2.b;
	if (res.r > 255)
		res.r = 255;
	if (res.g > 255)
		res.g = 255;
	if (res.b > 255)
		res.b = 255;
	return (res);
}

t_rgb	rgb_mult(t_rgb c1, t_rgb c2)
{
	t_rgb	res;

	res.r = c1.r * c2.r / 255;
	res.g = c1.g * c2.g / 255;
	res.b = c1.b * c2.b / 255;
	if (res.r > 255)
		res.r = 255;
	if (res.g > 255)
		res.g = 255;
	if (res.b > 255)
		res.b = 255;
	return (res);
}

t_rgb	rgb_avg(t_rgb c1, t_rgb c2)
{
	t_rgb	res;

	res.r = (c1.r + c2.r) / 2;
	res.g = (c1.g + c2.g) / 2;
	res.b = (c1.b + c2.b) / 2;
	if (res.r > 255)
		res.r = 255;
	if (res.g > 255)
		res.g = 255;
	if (res.b > 255)
		res.b = 255;
	return (res);
}

t_rgb	rgb_scale(t_rgb c, double j)
{
	t_rgb	res;

	res.r = c.r * j;
	res.g = c.g * j;
	res.b = c.b * j;
	if (res.r > 255)
		res.r = 255;
	if (res.g > 255)
		res.g = 255;
	if (res.b > 255)
		res.b = 255;
	if (res.r < 0)
		res.r = 0;
	if (res.g < 0)
		res.g = 0;
	if (res.b < 0)
		res.b = 0;
	return (res);
}
