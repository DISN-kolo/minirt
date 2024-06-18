/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akozin <akozin@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:05:46 by akozin            #+#    #+#             */
/*   Updated: 2024/04/30 14:37:37 by akozin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
void	*free_all(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (NULL);
}
*/
char	*gnl_strjoin_free(char *b1, char *b2)
{
	char	*t;

	t = gnl_strjoin(b1, b2);
	free(b1);
	return (t);
}

/* i += 1 ensures we move past '\n'
 */
char	*get_remainder(char *buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	line = gnl_calloc(gnl_strlen(buf) - i + 1, 1);
	if (!line)
		return (NULL);
	i += 1;
	j = 0;
	while (buf[i])
		line[j++] = buf[i++];
	free(buf);
	return (line);
}

char	*extract_line(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	if (!buf[0])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	line = gnl_calloc(i + 2, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i] = '\n';
	return (line);
}

/* the first if (!here) ensures that if we're starting
 * we get at least something. in the subsequent calls,
 * this if will be skipped over
 */
char	*read_one(int fd, char *here)
{
	char	*buf_ro;
	int		r;

	if (!here)
		here = gnl_calloc(1, 1);
	if (!here)
		return (NULL);
	buf_ro = gnl_calloc(BUFFER_SIZE + 1, 1);
	if (!buf_ro)
		return (NULL);
	r = 1;
	while (r > 0)
	{
		r = read(fd, buf_ro, BUFFER_SIZE);
		if (r == -1)
			return (free(buf_ro), free(here), NULL);
		buf_ro[r] = '\0';
		here = gnl_strjoin_free(here, buf_ro);
		if (!here)
			return (free(buf_ro), NULL);
		if (gnl_strchr(here, '\n'))
			break ;
	}
	free(buf_ro);
	return (here);
}

/* order of operations:
 * 1. read into the buffer until we meet a '\n' or EOF (r == 0)
 * 2. extract a string ending with '\n', if available, or just
 * a regular string that ends with the file ending.
 * 3. advance the buffer by re-starting it after the '\n', if
 * available, or just set it to NULL if it's over.
 */
char	*get_next_line(int fd)
{
	static char	*buf;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	buf = read_one(fd, buf);
	if (!buf)
		return (NULL);
	ret = extract_line(buf);
	buf = get_remainder(buf);
	return (ret);
}
/* shout-outs to jdecorte-be on github */
