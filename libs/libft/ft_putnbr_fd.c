/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:04:17 by akozin            #+#    #+#             */
/*   Updated: 2024/01/13 14:58:19 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int i, int p)
{
	int	ii;

	ii = i;
	if (!p)
		return (1);
	while (--p)
		i *= ii;
	return (i);
}

static int	ft_nbrlen(int x)
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

/* s = sign, w = letter ("w" for "word" because i'm stoopid
 * dc = digit counter, goes from left to right (so from high to low,
 * as it's basically the order of the current number as in 10^dc y'know */
void	ft_putnbr_fd(int n, int fd)
{
	char	w;
	int		s;
	int		dc;

	dc = ft_nbrlen(n);
	s = 1 - 2 * (n < 0);
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (dc >= 10)
	{
		w = s * (n / ft_pow(10, --dc)) + '0';
		ft_putchar_fd(w, fd);
	}
	while (dc)
	{
		w = s * (n / ft_pow(10, dc - 1)) - 10 * s *(n / ft_pow(10, dc)) + '0';
		ft_putchar_fd(w, fd);
		dc--;
	}
}
