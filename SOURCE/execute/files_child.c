/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:42:43 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/21 12:22:59 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_child_proxs(int infile, int out_fd, t_comnd *cmd, t_shell *shell)
{
	if (infile >= 0)
		dup2(infile, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	if (infile >= 0)
		close(infile);
	if (out_fd >= 0)
		close(out_fd);
	ft_execve_cmd_flat(cmd->av_cmd, shell->env_list);
	exit(EXIT_FAILURE);
}

void	ft_frk_chld(t_comnd *cmd, int pipe_fd[2], int prev_infi, t_shell *shell)
{
	pid_t	child;

	if (pipe(pipe_fd) < 0)
		ft_error_exit("pipe");
	child = fork();
	ft_check_fork(child);
	if (child == 0)
	{
		close(pipe_fd[0]);
		if (prev_infi >= 0)
		{
			dup2(prev_infi, STDIN_FILENO);
			close(prev_infi);
		}
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		open_infile(cmd, 1);
		open_outfile(cmd, 0, cmd->infile);
		ft_execve_cmd_flat(cmd->av_cmd, shell->env_list);
		cleanup_command_fds(cmd);
		exit(EXIT_FAILURE);
	}
	if (prev_infi >= 0)
		close(prev_infi);
	close(pipe_fd[1]);
}
