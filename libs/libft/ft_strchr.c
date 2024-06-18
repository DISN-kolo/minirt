/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:37:20 by akozin            #+#    #+#             */
/*   Updated: 2024/01/13 17:40:11 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	*retme;

	retme = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			retme = (char *)s;
			break ;
		}
		s++;
	}
	if ((unsigned char)c == 0 && *s == 0)
		retme = (char *)s;
	return (retme);
}
