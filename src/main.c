/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:29:46 by akozin            #+#    #+#             */
/*   Updated: 2024/07/16 12:29:20 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static void	data_init(t_data *data)
{
	data->light_n = 0;
	data->obj_n = 0;
	data->cam_n = 0;
	data->amb_n = 0;
	data->error = NULL_ERR;
	data->lights = NULL;
	data->objs = NULL;
}

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac != 2)
		return (print_usage(av[0]), 1);
	data_init(&data);
	fd = file_probe(&data, av[1]);
	if (data.error != NULL_ERR)
		err_exit(&data, 1, -2);
	parser_counter(&data, fd);
	if (data.error != NULL_ERR)
		err_exit(&data, 1, fd);
	else
		printf("counted Ls: %d\ncounted objs: %d\n", data.light_n, data.obj_n);
	close(fd);
	return (0);
}
