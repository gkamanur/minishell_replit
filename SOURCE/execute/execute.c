/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:59:45 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/02 16:35:20 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_cmds(t_comnd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	is_parent_builtin(t_comnd *cmd)
{
	if (!cmd->next && is_builtin_argv(cmd->av_cmd))
		if (!ft_strcmp(cmd->av_cmd[0], "cd") || !ft_strcmp(cmd->av_cmd[0],
				"export") || !ft_strcmp(cmd->av_cmd[0], "unset")
			|| !ft_strcmp(cmd->av_cmd[0], "exit"))
			return (1);
	return (0);
}

// void	run_child(t_pipe *ctx)
// {
// 	redirect_input(ctx->cmd, ctx->prev);
// 	redirect_output(ctx->cmd, ctx->pfd);
// 	if (ctx->pfd[0] >= 0)
// 		close(ctx->pfd[0]);
// 	if (ctx->pfd[1] >= 0)
// 		close(ctx->pfd[1]);
// 	if (ctx->prev >= 0)
// 		close(ctx->prev);
// 	if (is_builtin_argv(ctx->cmd->av_cmd))
// 	{
// 		exit(ft_dispatch_builtin(ctx->cmd->av_cmd, &ctx->shell->env_list,
// 				ctx->shell));
// 	}
// 	exec_command(ctx->cmd, ctx->envp);
// 	exit(1);
// }




void run_child(t_pipe *ctx)
{
    t_comnd *cmd = ctx->cmd;

    // Apply input/output redirections
	if (cmd->outfile == -2) // Redirection failed
    {
        exit(1); // Exit with error code 1
    }
    redirect_input(cmd, ctx->prev);
    redirect_output(cmd, ctx->pfd);

    // Close unused pipe ends
    if (ctx->pfd[0] >= 0) close(ctx->pfd[0]);
    if (ctx->pfd[1] >= 0) close(ctx->pfd[1]);
    if (ctx->prev >= 0) close(ctx->prev);

    // Check if it's a builtin
    if (is_builtin_argv(cmd->av_cmd))
    {
        exit(ft_dispatch_builtin_with_arrays(cmd->av_cmd, &ctx->shell->env_list, ctx->shell));
    }

    // Execute external command
    exec_command(cmd, ctx->envp);

    // If exec_command fails, exit to avoid child continuing
    exit(1);
}


void	ft_wait_all(pid_t *pids, int count, t_shell *shell)
{
	int	i;
	int	status;
	int last_status;

	i = 0;
	last_status = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	shell->last_status = last_status;
}
