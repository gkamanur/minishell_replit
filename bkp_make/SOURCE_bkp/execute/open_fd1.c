/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:44:50 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/21 12:07:27 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_infile(t_comnd *cmd, int in_child)
{
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = open(cmd->infile_name, O_RDONLY);
	if (cmd->infile < 0)
	{
		// Always print the error message (like bash does)
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->infile_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		
		if (in_child)
			exit(1);
		else
			cmd->infile = -1;
	}
}

static void	close_existing_outfile(t_comnd *last)
{
	if (last->outfile != -1)
	{
		close(last->outfile);
		last->outfile = -1;
	}
}

static void	open_from_heredoc(t_comnd *last, int infile_fd)
{
	if (infile_fd >= 0)
		last->outfile = dup(infile_fd);
	else
		last->outfile = -1;
}

static void	open_normal_outfile(t_comnd *last)
{
	if (last->redirec_type == TOKEN_REDIRECT_OUT)
		last->outfile = open(last->outfile_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (last->redirec_type == TOKEN_APPEND)
		last->outfile = open(last->outfile_name,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		last->outfile = -1;
	if (last->outfile < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(last->outfile_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		last->outfile = -1;
	}
}

void	open_outfile(t_comnd *last, int here_flag, int infile_fd)
{
	if (!last || !last->outfile_name)
		return ;
	close_existing_outfile(last);
	if (here_flag)
		open_from_heredoc(last, infile_fd);
	else
		open_normal_outfile(last);
	
	// If output redirection failed, mark it so the child process can handle it
	if (last->outfile < 0)
	{
		// Set a flag to indicate redirection failure
		last->outfile = -2; // Use -2 to indicate "redirection failed"
	}
}

// void	open_outfile(t_comnd *last, int here_flag, int infile_fd, int in_child)
// {
// 	(void)in_child;
// 	if (!last || !last->outfile_name)
// 		return ;
// 	if (last->outfile != -1)
// 	{
// 		close(last->outfile);
// 		last->outfile = -1;
// 	}
// 	if (here_flag)
// 	{
// 		if (infile_fd >= 0)
// 			last->outfile = dup(infile_fd);
// 		else
// 			last->outfile = -1;
// 		return ;
// 	}
// 	if (last->redirec_type == TOKEN_REDIRECT_OUT)
// 		last->outfile = open(last->outfile_name, O_WRONLY | O_CREAT | O_TRUNC,
// 				0644);
// 	else if (last->redirec_type == TOKEN_APPEND)
// 		last->outfile = open(last->outfile_name, O_WRONLY | O_CREAT | O_APPEND,
// 				0644);
// 	else
// 		last->outfile = -1;
// 	if (last->outfile < 0)
// 	{
// 		perror("open_outfile");
// 		last->outfile = -1;
// 	}
// }
