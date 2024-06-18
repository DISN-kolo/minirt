/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:55:40 by akozin            #+#    #+#             */
/*   Updated: 2024/03/30 17:25:30 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static char	*ret_empty_s(void)
{
	char	*r;

	r = (char *)malloc(1);
	if (!r)
		return (NULL);
	r[0] = '\0';
	return (r);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ret_empty_s());
	while (start--)
	{
		s++;
		if (*s == 0 && start != 0)
			return (ret_empty_s());
	}
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, len + 1);
	return (ret);
}
