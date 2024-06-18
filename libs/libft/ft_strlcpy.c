/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:00:13 by akozin            #+#    #+#             */
/*   Updated: 2024/01/18 12:30:21 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

/*
static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dstclone;
	const unsigned char	*srcclone;

	dstclone = dst;
	srcclone = src;
	if (!dstclone && !srcclone)
		return (NULL);
	while (n)
	{
		*dstclone++ = *srcclone++;
		n--;
	}
	return (dst);
}

static size_t	ft_strlen(const char *s)
{
	size_t	cur;

	cur = 0;
	while (s[cur])
		cur++;
	return (cur);
}
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;

	slen = ft_strlen(src);
	if (slen + 1 < dstsize)
		ft_memcpy(dst, src, slen + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (slen);
}
