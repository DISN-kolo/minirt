/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:37:42 by akozin            #+#    #+#             */
/*   Updated: 2024/01/18 12:51:17 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_in(char c, char const *set)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	start_f(char const *s1, char const *set)
{
	int	i;

	i = 0;
	if (!is_in(s1[i], set))
		return (0);
	while (s1[i++])
	{
		if (is_in(s1[i - 1], set) && !is_in(s1[i], set))
			return (i);
	}
	return (-1);
}

static int	end_f(char const *s1, char const *set)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	while (s1[i++])
	{
		if (is_in(s1[i], set) && !is_in(s1[i - 1], set))
			end = i;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;

	i = start_f(s1, set);
	if (i == -1)
	{
		ret = (char *)malloc(1);
		if (!ret)
			return (NULL);
		ret[0] = 0;
		return (ret);
	}
	ret = (char *)malloc(end_f(s1, set) - i + 1);
	if (!ret)
		return (NULL);
	while (i < end_f(s1, set))
	{
		ret[i - start_f(s1, set)] = s1[i];
		i++;
	}
	ret[i - start_f(s1, set)] = 0;
	return (ret);
}
