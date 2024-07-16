/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:21:37 by akozin            #+#    #+#             */
/*   Updated: 2024/07/16 12:30:03 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	free_all(t_data *data)
{
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
