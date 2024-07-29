/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosta-f < fcosta-f@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:48:10 by akozin            #+#    #+#             */
/*   Updated: 2024/07/20 17:21:49 by fcosta-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	test_drawing_lol(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = data->obj_n - 1;
	if (data->obj_n == 0)
		return ;
	int	stepx = 1920/data->obj_n;
	int	stepy = 1080/data->obj_n;
	while (i >= 0)
	{
		printf("%d %d %d\n",
				data->objs[i].color.r,
				data->objs[i].color.g,
				data->objs[i].color.b
				);
		x = 0;
		while (x < (i + 1) * stepx)
		{
			y = 0;
			while (y < (i + 1) * stepy)
				my_mlx_pixel_put(&data->img, x, y++,
					rgb_to_int(data->objs[i].color));
			x++;
		}
		i--;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
