/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:36:33 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/20 14:25:11 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	calc_total_len(char **av_cmd)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (av_cmd[i])
	{
		len += ft_strlen(av_cmd[i]);
		if (av_cmd[i + 1])
			len++;
		i++;
	}
	return (len + 1);
}

char	*ft_join_arguments(char **av_cmd)
{
	char	*joined;
	int		i;

	if (!av_cmd || !*av_cmd)
		return (NULL);
	joined = malloc(calc_total_len(av_cmd));
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	i = 0;
	while (av_cmd[i])
	{
		ft_strcat(joined, av_cmd[i]);
		if (av_cmd[i + 1])
			ft_strcat(joined, " ");
		i++;
	}
	return (joined);
}

void	ft_check_fork(pid_t child_pid)
{
	if (child_pid < 0)
		ft_error_exit("fork");
}

void	ft_error_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

void	ft_free_strings(char **cmd_array)
{
	int	i;

	i = 0;
	while (cmd_array[i])
	{
		free(cmd_array[i]);
		i++;
	}
	free(cmd_array);
}
