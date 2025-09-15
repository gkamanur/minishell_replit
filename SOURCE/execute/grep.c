/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:52:43 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/15 10:40:42 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_grep(const char *fullpath)
{
	const char *basename;

	if (!fullpath)
		return (0);
	basename = ft_strrchr(fullpath, '/');
	if (basename)
		basename++;  // Skip the '/'
	else
		basename = fullpath;
	if (ft_strcmp(basename, "grep") == 0)
		return (1);
	return (0);
}

static char	*join_args(char **args, const char *separator)
{
	char	*joined;
	//char	*temp;
	size_t	total_len;
	int		i;

	if (!args || !args[0])
		return (NULL);
	total_len = 0;
	i = 0;
	while (args[i])
	{
		total_len += ft_strlen(args[i]);
		if (args[i + 1])
			total_len += ft_strlen(separator);
		i++;
	}
	joined = ft_calloc(total_len + 1, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (args[i])
	{
		ft_strlcat(joined, args[i], total_len + 1);
		if (args[i + 1])
			ft_strlcat(joined, separator, total_len + 1);
		i++;
	}
	return (joined);
}

void	execve_grep_handler(const char *fullpath, t_comnd *current, char **envp)
{
	char	*joined;
	char	*new_argv[3];
	// if (fullpath && current->av_cmd && ft_strcmp(current->av_cmd[1], "-") == 0)
	// 	execve(fullpath, current->av_cmd, envp);
	if (is_grep(fullpath) && current->av_cmd && current->av_cmd[1])
	{
		joined = join_args(&current->av_cmd[1], "");
        //printf("Joined args for grep: [%s]\n", joined); // Debugging line
		if (!joined)
		{
			ft_putstr_fd("minishell: memory allocation failed", 2);
			exit(EXIT_FAILURE);
		}
		new_argv[0] = ft_strdup(current->av_cmd[0]);
		if (!new_argv[0])
		{
			free(joined);
			ft_putstr_fd("minishell: memory allocation failed", 2);
			exit(EXIT_FAILURE);
		}
		new_argv[1] = joined;
		new_argv[2] = NULL;
		execve(fullpath, new_argv, envp);
		free(new_argv[0]);
		free(joined);
	}
    else
    {
        execve(fullpath, current->av_cmd, envp);
    }
	ft_putstr_fd("minishell: execve failed", 2);
	exit(EXIT_FAILURE);
}
