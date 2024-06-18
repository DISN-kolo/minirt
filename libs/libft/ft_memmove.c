/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:25:40 by akozin            #+#    #+#             */
/*   Updated: 2024/01/13 17:22:45 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dstclone;
	const unsigned char	*srcclone;

	dstclone = dst;
	srcclone = src;
	if (!dstclone && !srcclone)
		return (NULL);
	if (dstclone > srcclone)
	{
		while (len--)
			dstclone[len] = srcclone[len];
	}
	else if (dstclone < srcclone)
	{
		while (len--)
			*dstclone++ = *srcclone++;
	}
	return (dst);
}
