/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:29:46 by akozin            #+#    #+#             */
/*   Updated: 2024/07/15 17:27:52 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	print_usage(char *s)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" <FILE.rt>\n", 2);
}

void	data_init(t_data *data)
{
	data->light_n = 0;
	data->obj_n = 0;
	data->cam_n = 0;
	data->amb_n = 0;
	data->error = NULL_ERR;
}

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac != 2)
		return (print_usage(av[0]), 1);
	data_init(&data);
	fd = file_probe(&data, av[1]);
	if (data.error == FILE_ERR)
		return (ft_putstr_fd("Can't open file\n", 2), 1);
	else if (data.error == FNAME_ERR)
		return (ft_putstr_fd("File must end in '.rt'\n", 2), 1);
	printf("file open OK\n");
	parser_counter(&data, fd);
	if (data.error != NULL_ERR)
		return (close(fd), printf("fail parse\n"), 1);
	else
		printf("counted Ls: %d\ncounted objs: %d\n", data.light_n, data.obj_n);
	close(fd);
	printf("file close OK\n");
	return (0);
}
