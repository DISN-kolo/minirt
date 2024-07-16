/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:14:04 by akozin            #+#    #+#             */
/*   Updated: 2024/07/16 12:30:25 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * see ../../inc/minirt.h for the enum t_err
 */
static void	print_err(t_data *data)
{
	if (data->error == FLOAT_ERR)
		ft_putstr_fd("Incorrectly entered float\n", 2);
	else if (data->error == TYPE_ERR)
		ft_putstr_fd("Unknown line encountered\n", 2);
	else if (data->error == FILE_ERR)
		ft_putstr_fd("Can't open file\n", 2);
	else if (data->error == FNAME_ERR)
		ft_putstr_fd("File must end in '.rt'\n", 2);
	else if (data->error == TOO_MUCH_ERR)
		ft_putstr_fd("Too many (> 1) objects of either A or C type\n", 2);
}

/*
 * fd_to_close will be closed if it exists. so, in case we
 * do not need to close anything, we just pass a -2
 * we don't pass -1 because it's reserved for open() failures
 */
void	err_exit(t_data *data, int code, int fd_to_close)
{
	if (fd_to_close != -2)
		close(fd_to_close);
	print_err(data);
	free_all(data);
	exit(code);
}
