/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileprobe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:37:56 by akozin            #+#    #+#             */
/*   Updated: 2024/07/15 16:48:21 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	file_probe(t_data *data, char *s)
{
	char	*finpt;
	int		fd;

	finpt = ft_strrchr(s, '.');
	if (!finpt)
		return (data->error = FNAME_ERR, -1);
	if (!ft_strncmp(finpt, ".rt", 4))
	{
		fd = open(s, O_RDONLY);
		if (fd == -1)
			return (data->error = FILE_ERR, -1);
		return (fd);
	}
	return (data->error = FNAME_ERR, -1);
}
