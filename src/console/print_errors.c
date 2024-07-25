/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:14:04 by akozin            #+#    #+#             */
/*   Updated: 2024/07/25 16:07:25 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * see ../../inc/minirt.h for the enum t_err
 */
static void	print_err_2(t_data *data)
{
	if (data->error == NO_CAM_ERR)
		ft_putstr_fd("The scene must have a camera\n", 2);
	else if (data->error == NORMAL_ERR)
		ft_putstr_fd("Poorly entered normal\n", 2);
	else
		ft_putstr_fd("Unknown error\n", 2);
}

void	print_err(t_data *data)
{
	ft_putstr_fd("Error\n", 2);
	if (data->error == DOUBLE_ERR)
		ft_putstr_fd("Incorrectly entered double\n", 2);
	else if (data->error == ORIGIN_ERR)
		ft_putstr_fd("Incorrectly entered floating point vector. \
Format: X,Y,Z\n", 2);
	else if (data->error == RGB_ERR)
		ft_putstr_fd("Incorrectly entered RGB. Ranges: 0..255, \
format: R,G,B\n", 2);
	else if (data->error == FOV_ERR)
		ft_putstr_fd("Incorrectly entered FOV. Ranges: 0..180\n", 2);
	else if (data->error == TYPE_ERR)
		ft_putstr_fd("Unknown line encountered\n", 2);
	else if (data->error == FILE_ERR)
		ft_putstr_fd("Can't open file\n", 2);
	else if (data->error == FNAME_ERR)
		ft_putstr_fd("File must end in '.rt'\n", 2);
	else if (data->error == TOO_MANY_OBJS_ERR)
		ft_putstr_fd("Too many (> 1) objects of either A or C type\n", 2);
	else if (data->error == PARAM_N_ERR)
		ft_putstr_fd("Wrong number of parameters on some line\n", 2);
	else if (data->error == MALLOC_ERR)
		ft_putstr_fd("Malloc error\n", 2);
	else
		print_err_2(data);
}
