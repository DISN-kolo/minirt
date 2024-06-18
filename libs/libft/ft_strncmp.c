/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:33:54 by akozin            #+#    #+#             */
/*   Updated: 2024/01/18 13:02:35 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		p;
	size_t	c;

	if (n == 0)
		return (0);
	p = 0;
	c = 0;
	while ((unsigned char)s1[p] != 0 && (unsigned char)s2[p] != 0 && c < n)
	{
		if ((unsigned char)s1[p] != (unsigned char)s2[p])
			return ((unsigned char)s1[p] - (unsigned char)s2[p]);
		p++;
		c++;
	}
	if ((unsigned char)s1[p] != (unsigned char)s2[p] && c < n)
		return ((unsigned char)s1[p] - (unsigned char)s2[p]);
	return (0);
}
