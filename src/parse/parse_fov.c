/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:24:22 by akozin            #+#    #+#             */
/*   Updated: 2024/07/17 15:41:12 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parse_fov(t_data *data, char *s)
{
	int		res;
	char	*probe;

	probe = s;
	while (*probe && *probe != '\n' && *probe != ' ')
	{
		if (!ft_isdigit(*probe))
			return (data->error = FOV_ERR, -1);
		probe++;
	}
	res = ft_atoi(s);
	if (res < 0 || res > 180)
		return (data->error = FOV_ERR, -1);
	return (res);
}
