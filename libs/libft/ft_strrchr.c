/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:37:20 by akozin            #+#    #+#             */
/*   Updated: 2024/01/18 11:57:47 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*retme;

	retme = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			retme = (char *)s;
		s++;
	}
	if ((unsigned char)c == 0 && *s == 0)
		retme = (char *)s;
	return (retme);
}
