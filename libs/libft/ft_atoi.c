/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:07:12 by akozin            #+#    #+#             */
/*   Updated: 2024/07/15 15:46:37 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isn(char x)
{
	return (x >= '0' && x <= '9');
}

int	ft_atoi(char *src)
{
	int	res;

	res = 0;
	while (*src && *src != '\n')
	{
		res *= 10;
		if (ft_isn(*src))
			res += *src - '0';	
		else
			return (-1);
		src++;
	}
	return (res);
}
// dead simple version for positive numbers only. spaces BEGONE
// used since we have only 0..255 as ints
/*
	while (*src != '\n' && ft_isspace(*src))
		src++;
*/
// spaces hello ^^^^^ just in case
