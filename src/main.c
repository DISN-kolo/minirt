/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:29:46 by akozin            #+#    #+#             */
/*   Updated: 2024/07/15 16:51:45 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	print_usage(char *s)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" <FILE.rt>\n", 2);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac != 2)
		return (print_usage(av[0]), 1);
	fd = file_probe(&data, av[1]);
	if (data.error == FILE_ERR)
		return (ft_putstr_fd("Can't open file\n", 2), 1);
	else if (data.error == FNAME_ERR)
		return (ft_putstr_fd("File must end in '.rt'\n", 2), 1);
	printf("file open OK\n");
	close(fd);
	printf("file close OK\n");
	return (0);
}
