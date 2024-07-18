/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:29:46 by akozin            #+#    #+#             */
/*   Updated: 2024/07/18 16:36:41 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (print_usage(av[0]), 1);
	data_init(&data);
	file_reading(&data, av);
	mlx_setting_up(&data);
	printf("img: %p\nadd: %p\n", data.img.img, data.img.addr);
	test_drawing_lol(&data);
	mlx_loop(data.mlx);
	free_all(&data);
	return (0);
}
