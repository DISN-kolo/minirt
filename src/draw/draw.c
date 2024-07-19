/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:48:10 by akozin            #+#    #+#             */
/*   Updated: 2024/07/18 16:43:20 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	draw(t_data *data)
{
	int		px;
	int		py;
	t_vec3	f;
	t_vec3	r;
	t_vec3	u;
	double	plane_col;

	px = 0;
	r.x = -1;
	r.y = 0;
	r.z = 0;
	u.x = 0;
	u.y = 1;
	u.z = 0;
	while (px < WIN_X + 1)
	{
		py = 0;
		while (py < WIN_Y)
		{
			f = vec_add(data->cam.normal,
					vec_scale(r,
						tan(data->cam.fov / 2.) *
						(2 * px / WIN_X - 1)));
			f = vec_add(f,
					vec_scale(u,
						WIN_Y / WIN_X *
						tan(data->cam.fov / 2.) *
						(2 * py / WIN_Y - 1)));
			normalize(&f);
			//printf("the vector would be %f %f %f\n\n", f.x, f.y, f.z);
			plane_col = splane_ray(data->cam.origin, f, data->objs[0].origin, data->objs[0].normal);
			if (!isinf(plane_col))
			{
			//	printf("ray sent in %4d %4d hits plane at distance %10f from the origin\n", px, py, plane_col);
				my_mlx_pixel_put(&data->img, px, py++,
					rgb_to_int(data->objs[0].color));
			}
			else
				my_mlx_pixel_put(&data->img, px, py++,
					rgb_to_int(data->amb.color));
		}
		px++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
/*
 * some notes:
 * 
 * amb light is probably the background color
 *
 * camera's normal vector is added to up and right vectors, multiplied
 * by corresponding coeffs to 1. go thru pixels 2. convert w/ the ratio
 * 3. take FOV into account. speaking of, we're gonna have the fov as vertical
 *
 * (imaginary img plane (= screen) things:)
 * screen height  = 2*h
 * screen width   = 2*w
 * used fov angle = given fov / 2
 *
 * considering the forward vector (cam's normal) is normalized,
 * h / 1 = tan (fov)
 * h = tan(fov)
 * w = h * ratio = h * WIN_X / WIN_Y = tan(fov) * WIN_X/WIN_Y
 *
 * representing a point on this imaginary plane with up and right vectors:
 * a*u + b*r = p
 * where a goes: -h..h
 * and   b       -w..w
 *
 * -w                    +w
 * _______________________ +h
 * |                     |
 * |         ^ u         |
 * |         |           |
 * |         . --> r     |
 * |                     |
 * |                     |
 * |_____________________| -h
 *
 * okay, so if we add this to our forward vector, we get the vector from the
 * camera's origin point through the specified point on the rendering plane:
 * f + h*y*u + w*x*r
 * here, x and y: -1..1
 *
 * so, coming back to the WIN_X WIN_Y values for the actual pixels we'll use,
 * we need to convert x from 0..WIN_X to -1..1, and y has a similar story
 * px: 0..WIN_X
 * x: -1..1
 * => x = 2 * px / WIN_X - 1
 * so, for y,
 * => y = 2 * py / WIN_Y - 1
 *
 * so for our scene, x is to the right, y is up, and z is depth.
 *
 * this should be enough.
 */
