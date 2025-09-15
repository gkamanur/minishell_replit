/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:40:56 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/21 12:01:19 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"




void	redirect_input(t_comnd *c, int prev, int is_first_cmd)
{
	if (c->infile >= 0)
	{
		dup2(c->infile, 0);
		close(c->infile);
	}
	else if (prev >= 0)
		dup2(prev, 0);
	else if (!is_first_cmd)
	{
		// Only redirect to /dev/null if not the first command in pipeline
		int devnull = open("/dev/null", O_RDONLY);
		if (devnull >= 0)
		{
			dup2(devnull, 0);
			close(devnull);
		}
	}
	// If is_first_cmd is true and no prev/infile, preserve original stdin
	// This allows commands like 'cat' in 'cat | cat | ls' to wait for input
}

void	redirect_output(t_comnd *c, int *pfd)
{
	if (c->outfile >= 0)
	{
		dup2(c->outfile, 1);
		close(c->outfile);
	}
	else if (pfd[1] >= 0)
		dup2(pfd[1], 1);
}

void	cleanup_all_fds(t_comnd *cmds)
{
	t_comnd	*current;

	current = cmds;
	while (current)
	{
		cleanup_command_fds(current);
		current = current->next;
	}
}

void	cleanup_command_fds(t_comnd *cmd)
{
	if (cmd->infile != -1)
	{
		close(cmd->infile);
		cmd->infile = -1;
	}
	if (cmd->outfile != -1)
	{
		close(cmd->outfile);
		cmd->outfile = -1;
	}
}

void	ft_put_exec_error(char *cmd, char **cmd_array, char *fullpath)
{
	ft_putstr_fd("minishell: line 1: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	free(fullpath);
	ft_free_strings(cmd_array);
	exit(EXIT_FAILURE);
}
