/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:31:34 by akozin            #+#    #+#             */
/*   Updated: 2024/01/10 13:09:58 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/*
static size_t	ft_strlen(const char *s)
{
	size_t	cur;

	cur = 0;
	while (s[cur])
		cur++;
	return (cur);
}
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*dstclone;
	const char	*srcclone;
	size_t		n;
	size_t		dlen;

	dstclone = dst;
	srcclone = src;
	n = dstsize;
	while (n-- && *dstclone)
		dstclone++;
	dlen = dstclone - dst;
	n = dstsize - dlen;
	if (n == 0)
		return (dlen + ft_strlen(srcclone));
	while (*srcclone)
	{
		if (n != 1)
		{
			*dstclone++ = *srcclone;
			n--;
		}
		srcclone++;
	}
	*dstclone = '\0';
	return (dlen + (srcclone - src));
}
