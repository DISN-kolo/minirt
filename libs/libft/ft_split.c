/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:11:30 by akozin            #+#    #+#             */
/*   Updated: 2024/03/25 12:54:40 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
static int	is_w(char c, char *set)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (set[i])
	{
		if (c == set[i++])
			return (0);
	}
	return (1);
}
*/
int	wc(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s[i])
		return (0);
	if (s[i++] != c)
		count++;
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	char	**ret;
	size_t	wlen;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof (char *) * (wc(str, c) + 1));
	if (!ret)
		return (NULL);
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str)
		{
			if (!ft_strchr(str, c))
				wlen = ft_strlen(str);
			else
				wlen = ft_strchr(str, c) - str;
			ret[i++] = ft_substr(str, 0, wlen);
			str += wlen;
		}
	}
	ret[i] = NULL;
	return (ret);
}
