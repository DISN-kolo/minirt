/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:12:39 by akozin            #+#    #+#             */
/*   Updated: 2024/07/16 12:30:17 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	print_usage(char *s)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" <FILE.rt>\n", 2);
}
