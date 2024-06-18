/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:25:40 by akozin            #+#    #+#             */
/*   Updated: 2024/01/13 17:19:46 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
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
