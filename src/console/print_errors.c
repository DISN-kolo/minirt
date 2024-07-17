/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:14:04 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 14:47:15 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * see ../../inc/minirt.h for the enum t_err
 */
void	print_err(t_data *data)
{
	if (data->error == DOUBLE_ERR)
		ft_putstr_fd("Incorrectly entered double\n", 2);
	else if (data->error == ORIGIN_ERR)
		ft_putstr_fd("Incorrectly entered floating point vector\n", 2);
	else if (data->error == RGB_ERR)
		ft_putstr_fd("Incorrectly entered RGB\n", 2);
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
}
