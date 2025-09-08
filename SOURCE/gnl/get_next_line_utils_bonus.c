/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:02:54 by robello-          #+#    #+#             */
/*   Updated: 2025/08/22 10:17:08 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clear_all_buffs(t_buffer *bufs, int max_fds)
{
	int	x;

	x = 0;
	while (x < max_fds)
	{
		clear_buff(&bufs[x]);
		x++;
	}
}

size_t	my_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*append_to_line(char *line, const char *chunk, ssize_t clen)
{
	char	*new_line;
	size_t	llen;
	size_t	total;
	size_t	i;

	llen = my_strlen(line);
	total = llen + clen;
	new_line = malloc(total + 1);
	if (!new_line)
		return (free(line), NULL);
	i = 0;
	while (i < llen)
	{
		new_line[i] = line[i];
		i++;
	}
	i = 0;
	while (i < (size_t)clen)
	{
		new_line[llen + i] = chunk[i];
		i++;
	}
	new_line[total] = '\0';
	free(line);
	return (new_line);
}

ssize_t	allocate_buffer(t_buffer *buf)
{
	if (!buf->buffer)
	{
		buf->buffer = malloc(BUFFER_SIZE + 1);
		if (!buf->buffer)
		{
			buf->bytes_read = -1;
			return (-1);
		}
	}
	return (0);
}

ssize_t	read_update(int fd, t_buffer *buf)
{
	ssize_t	read_result;

	if (buf->offset >= buf->bytes_read)
	{
		if (allocate_buffer(buf) == -1)
			return (-1);
		read_result = read(fd, buf->buffer, BUFFER_SIZE);
		if (read_result < 0 || read_result == 0)
		{
			if (read_result < 0)
				buf->bytes_read = -1;
			free(buf->buffer);
			buf->buffer = NULL;
			buf->bytes_read = 0;
			buf->offset = 0;
			return (read_result);
		}
		buf->bytes_read = read_result;
		buf->offset = 0;
		buf->buffer[read_result] = '\0';
	}
	return (buf->bytes_read);
}
