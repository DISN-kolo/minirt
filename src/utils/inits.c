/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:12:55 by akozin            #+#    #+#             */
/*   Updated: 2024/07/29 18:08:05 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	data_init(t_data *data)
{
	data->light_n = 0;
	data->c_light = 0;
	data->obj_n = 0;
	data->c_obj = 0;
	data->cam_n = 0;
	data->amb_n = 0;
	data->error = NULL_ERR;
	data->lights = NULL;
	data->objs = NULL;
	data->mlx = NULL;
	data->cy_b = -1;
}

void	allocate_stuff(t_data *data)
{
	data->lights = malloc(sizeof (t_light) * (data->light_n));
	if (!data->lights)
		return ((void)(data->error = MALLOC_ERR));
	data->objs = malloc(sizeof (t_obj) * (data->obj_n));
	if (!data->objs)
		return ((void)(data->error = MALLOC_ERR));
}

t_rgb	rgb_init(void)
{
	t_rgb	res;

	res.r = 0;
	res.g = 0;
	res.b = 0;
	return (res);
}

void	file_reading(t_data *data, char **av)
{
	int	fd;

	fd = file_probe(data, av[1]);
	if (data->error != NULL_ERR)
		err_exit(data, 1, -2);
	parser_counter(data, fd);
	if (data->error != NULL_ERR)
		err_exit(data, 1, fd);
	close(fd);
	allocate_stuff(data);
	if (data->error != NULL_ERR)
		err_exit(data, 1, -2);
	fd = file_probe(data, av[1]);
	if (data->error != NULL_ERR)
		err_exit(data, 1, -2);
	parser(data, fd);
	if (data->error != NULL_ERR)
		err_exit(data, 1, fd);
	close(fd);
}

void	mlx_setting_up(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_X, WIN_Y, "MiniRT");
	mlx_hook(data->win, 2, 1L << 0, key_hand, data);
	mlx_hook(data->win, 17, 0, x_hand, data);
	data->img.img = mlx_new_image(data->mlx, WIN_X, WIN_Y);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&(*data).img.bits_per_pixel, &(*data).img.line_length,
			&(*data).img.endian);
}
