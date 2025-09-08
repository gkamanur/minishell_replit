/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:02:18 by robello-          #+#    #+#             */
/*   Updated: 2025/08/22 10:17:44 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clear_buff(t_buffer *buf)
{
	if (buf->buffer)
	{
		free(buf->buffer);
		buf->buffer = NULL;
	}
	buf->bytes_read = 0;
	buf->offset = 0;
}

char	*extract_chunk(t_buffer *buf)
{
	char	*chunk;
	ssize_t	clen;
	ssize_t	i;

	clen = 0;
	while (buf->offset + clen < buf->bytes_read
		&& buf->buffer[buf->offset + clen] != '\n')
		clen++;
	if (buf->offset + clen < buf->bytes_read
		&& buf->buffer[buf->offset + clen] == '\n')
		clen++;
	chunk = malloc(clen + 1);
	if (!chunk)
		return (NULL);
	i = -1;
	while (++i < clen)
		chunk[i] = buf->buffer[buf->offset + i];
	chunk[clen] = '\0';
	buf->offset += clen;
	return (chunk);
}

char	*process_chunk(char *line, t_buffer *buf)
{
	char	*chunk;
	char	*new_line;

	chunk = extract_chunk(buf);
	if (!chunk)
		return (free(line), NULL);
	new_line = append_to_line(line, chunk, my_strlen(chunk));
	free(chunk);
	return (new_line);
}

int	has_newline(char *line)
{
	size_t	len;

	if (!line)
		return (0);
	len = my_strlen(line);
	return (len > 0 && line[len - 1] == '\n');
}

char	*get_next_line(int fd)
{
	static t_buffer	bufs[MAX_FD];
	char			*line;
	t_buffer		*buf;
	ssize_t			read_status;

	if (fd == -1)
		return (clear_all_buffs(bufs, MAX_FD), NULL);
	buf = &bufs[fd];
	line = NULL;
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		read_status = read_update(fd, buf);
		if (read_status == -1)
			return (free(line), NULL);
		if (read_status == 0)
			return (clear_buff(buf), line);
		line = process_chunk(line, buf);
		if (!line)
			return (NULL);
		if (has_newline(line))
			break ;
	}
	return (line);
}
