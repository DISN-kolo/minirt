/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:29:46 by akozin            #+#    #+#             */
/*   Updated: 2024/07/16 13:57:24 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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
	close(fd);
	allocate_stuff(&data);
	if (data.error != NULL_ERR)
		err_exit(&data, 1, -2);
	fd = file_probe(&data, av[1]);
	if (data.error != NULL_ERR)
		err_exit(&data, 1, -2);
	parser(&data, fd);
	if (data.error != NULL_ERR)
		err_exit(&data, 1, fd);
	close(fd);
	free_all(&data);
	return (0);
}
