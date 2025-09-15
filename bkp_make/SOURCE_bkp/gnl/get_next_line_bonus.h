/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:04:01 by robello-          #+#    #+#             */
/*   Updated: 2025/08/22 10:15:07 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef MAX_FD
#  define MAX_FD 4096
# endif

# include <sys/uio.h>
# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <errno.h>

typedef struct s_buffer
{
	char	*buffer;
	ssize_t	offset;
	ssize_t	bytes_read;
}	t_buffer;

char	*append_to_line(char *line, const char *chunk, ssize_t clen);
ssize_t	allocate_buffer(t_buffer *buf);
ssize_t	read_update(int fd, t_buffer *buf);
void	clear_buff(t_buffer *buf);
char	*extract_chunk(t_buffer *buf);
char	*process_chunk(char *line, t_buffer *buf);
char	*get_next_line(int fd);
size_t	my_strlen(const char *str);
void	clear_all_buffs(t_buffer *bufs, int i);
int		has_newline(char *line);

#endif
