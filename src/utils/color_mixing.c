/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mixing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:42:12 by akozin            #+#    #+#             */
/*   Updated: 2024/07/25 14:42:14 by akozin           ###   ########.fr       */
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

t_rgb	rgb_clamp(t_rgb c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.g > 255)
		c.g = 255;
	if (c.b > 255)
		c.b = 255;
	if (c.r < 0)
		c.r = 0;
	if (c.g < 0)
		c.g = 0;
	if (c.b < 0)
		c.b = 0;
	return (c);
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

/*
 * the formula that's being replicated here:
 *
 * perceived_light = rgb_scale(data->lights[j].color, scale_factor);
 *
 * ret = rgb_add(ret, rgb_scale(rgb_avg(ret, perceived_light), 0.5));
 *
 * ret = rgb_add(ret, rgb_mult(ret, perceived_light));
 */
/*
return (rgb_add(ret, rgb_scale(additive, scale_factor)));
*/
t_rgb	super_mix(t_rgb ret, t_rgb additive, double scale_factor)
{
	t_vec3	vec_ret;
	t_vec3	vec_addit;

	vec_ret.x = ret.r / 255.;
	vec_ret.y = ret.g / 255.;
	vec_ret.z = ret.b / 255.;
	vec_addit.x = additive.r / 255.;
	vec_addit.y = additive.g / 255.;
	vec_addit.z = additive.b / 255.;
	vec_ret = vec_add(vec_ret, vec_scale(vec_addit, scale_factor));
	vec_addit.x *= vec_ret.x;
	vec_addit.y *= vec_ret.y;
	vec_addit.z *= vec_ret.z;
	vec_ret = vec_add(vec_ret, vec_scale(vec_addit, scale_factor));
	ret.r = vec_ret.x * 255;
	ret.g = vec_ret.y * 255;
	ret.b = vec_ret.z * 255;
	return (rgb_clamp(ret));
}
