/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:21:37 by akozin            #+#    #+#             */
/*   Updated: 2024/07/18 15:30:55 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	free_str_arr(char ***s)
{
	int	i;

	if (!*s)
		return ;
	i = 0;
	while ((*s)[i])
	{
		free((*s)[i]);
		(*s)[i] = NULL;
		i++;
	}
	free((*s));
	(*s) = NULL;
}

void	free_all(t_data *data)
{
	if (data->mlx)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
		data->mlx = NULL;
	}
	if (data->lights)
	{
		free(data->lights);
		data->lights = NULL;
	}
	if (data->objs)
	{
		free(data->objs);
		data->objs = NULL;
	}
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
