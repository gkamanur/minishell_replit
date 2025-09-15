/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:48:12 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/02 09:32:10 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_open_main(t_comnd *cmds, int here_flag)
{
	t_comnd	*current;

	if (g_gb.last_sig == SIGINT)
		return ;
	
	// Open redirections for each command in the pipeline
	// Don't abort pipeline - let individual commands handle their redirection failures
	current = cmds;
	while (current)
	{
		// Open input file if specified
		if (!here_flag && current->infile_name)
		{
			open_infile(current, 0);
			// Individual commands will handle their own redirection failures
		}
		
		// Open output file if specified
		if (current->outfile_name)
		{
			open_outfile(current, here_flag, -1);
			// Individual commands will handle their own redirection failures
		}
		
		current = current->next;
	}
}

void	ft_open_last_outfile(t_comnd *cmds)
{
	t_comnd	*last;
	int		flags;

	last = cmds;
	while (last && last->next)
		last = last->next;
	if (last && last->outfile_name)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		last->outfile = open(last->outfile_name, flags, 0644);
		if (last->outfile < 0)
		{
			perror(last->outfile_name);
			exit(EXIT_FAILURE);
		}
	}
}

int	devnull_open(int fd)
{
	fd = open("/dev/null", O_RDONLY);
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (fd);
}

void	ft_child_setup(t_comnd *current, int prev_fd, int pipe_write)
{
	int	devnull;

	(void)devnull;
	if (current->infile >= 0)
	{
		dup2(current->infile, STDIN_FILENO);
		close(current->infile);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	else
		devnull = devnull_open(-1);
	if (pipe_write >= 0)
	{
		dup2(pipe_write, STDOUT_FILENO);
		close(pipe_write);
	}
	if (current->outfile >= 0)
	{
		dup2(current->outfile, STDOUT_FILENO);
		close(current->outfile);
	}
}

// void	ft_child_setup(t_comnd *current, int prev_fd, int pipe_write)
// {
// 	int	devnull;

// 	if (current->infile >= 0)
// 	{
// 		dup2(current->infile, STDIN_FILENO);
// 		close(current->infile);
// 	}
// 	else if (prev_fd != -1)
// 	{
// 		dup2(prev_fd, STDIN_FILENO);
// 		close(prev_fd);
// 	}
// 	else
// 	{
// 		devnull = open("/dev/null", O_RDONLY);
// 		if (devnull >= 0)
// 		{
// 			dup2(devnull, STDIN_FILENO);
// 			close(devnull);
// 		}
// 	}
// 	if (pipe_write >= 0)
// 	{
// 		dup2(pipe_write, STDOUT_FILENO);
// 		close(pipe_write);
// 	}
// 	if (current->outfile >= 0)
// 	{
// 		dup2(current->outfile, STDOUT_FILENO);
// 		close(current->outfile);
// 	}
// }
