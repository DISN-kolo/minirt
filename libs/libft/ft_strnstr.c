/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:33:29 by akozin            #+#    #+#             */
/*   Updated: 2024/01/10 16:27:11 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*sp;
	char	*tfp;
	size_t	rlen;

	tfp = (char *)needle;
	if (*tfp == 0)
		return ((char *)haystack);
	while (*haystack != 0 && len != 0)
	{
		if (*haystack == *tfp)
		{
			sp = (char *)haystack;
			rlen = len;
			while (*sp++ == *tfp++ && len-- != 0)
			{
				if (*tfp == 0)
					return ((char *)haystack);
			}
			len = rlen;
			tfp = (char *)needle;
		}
		len--;
		haystack++;
	}
	return (NULL);
}
