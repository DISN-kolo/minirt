/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:46:13 by akozin            #+#    #+#             */
/*   Updated: 2024/05/27 11:18:42 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_p(int i, int p)
{
	int	ii;

	ii = i;
	if (!p)
		return (1);
	while (--p)
		i *= ii;
	return (i);
}

static int	ft_nbrlen(long x)
{
	int	count;

	count = 0;
	if (!x)
		return (1);
	while (x)
	{
		x /= 10;
		count++;
	}
	return (count);
}

/*
 * s = sign. computed by checking whether the number is less than 0
 * or not. the logic return 1 or 0 and the equation returns -1 or +1.
 * r = return array.
 * dc = digit counter. it is the index for running through r.
 * ds = digit "sum" (idk why i named it like that but it's the TOTAL
 * digit count at the start. it's getting less in orded to go through
 * the number's digits in reverse (from the biggest to the smallest)
 * because we're writing from left to right.
 */
char	*ft_itoa(long n)
{
	char	*r;
	int		ds;
	int		dc;
	int		s;

	r = (char *)malloc(ft_nbrlen(n) + 1 + (n < 0));
	if (!r)
		return (r);
	dc = 0;
	s = 1 - 2 * (n < 0);
	if (n < 0)
	{
		r[0] = '-';
		dc++;
	}
	ds = ft_nbrlen(n);
	if (ds >= 10)
		r[dc++] = s * (n / ft_p(10, --ds)) + '0';
	while (dc < (ft_nbrlen(n) + (n < 0)))
	{
		r[dc++] = s * ((n / ft_p(10, ds - 1)) - 10 * (n / ft_p(10, ds))) + '0';
		ds--;
	}
	r[dc] = 0;
	return (r);
}
