/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:24:22 by akozin            #+#    #+#             */
/*   Updated: 2024/07/29 12:37:43 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parse_fov(t_data *data, char *s)
{
	int		res;
	int		overfl_c;
	char	*probe;

	probe = s;
	overfl_c = 0;
	while (*probe && *probe != '\n' && *probe != ' ')
	{
		if (!ft_isdigit(*probe))
			return (data->error = FOV_ERR, -1);
		if ((overfl_c == 0 && *probe != '0')
			|| overfl_c != 0)
			overfl_c++;
		if (overfl_c > 3)
			return (data->error = FOV_ERR, -1);
		probe++;
	}
	res = ft_atoi(s);
	if (res < 0 || res > 180)
		return (data->error = FOV_ERR, -1);
	return (res);
}
