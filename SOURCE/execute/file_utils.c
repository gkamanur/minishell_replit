/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:05:59 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/21 12:06:38 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_open_file(char *filename, int mode, int permis)
{
	if (mode == O_RDONLY)
		return (open(filename, mode));
	else
		return (open(filename, mode, permis));
}

int	ft_open_outfile(char *filename, int here_flag)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (here_flag)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd < 0)
		perror("open file");
	return (fd);
}
