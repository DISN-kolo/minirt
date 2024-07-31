/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_internal_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:19:28 by akozin            #+#    #+#             */
/*   Updated: 2024/07/31 13:23:54 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/*
 * love poem for the norminette
 *
 * o dear norminette!
 * i wish you weren't real.
 */
int	ret_smthn_from_caps_if(double d1, double d2)
{
	return ((d1 > EPSILON && d1 < d2) || (d2 > EPSILON));
}

double	what_do_i_return_from_caps_if(double d1, double d2)
{
	if (d1 > EPSILON && d1 < d2)
		return (d1);
	else if (d2 > EPSILON)
		return (d2);
	return (INFINITY);
}
