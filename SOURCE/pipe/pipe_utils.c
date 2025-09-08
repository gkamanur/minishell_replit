/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:16:47 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/02 11:16:46 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	setup_allocations(t_comnd *cmds, t_shell *shell, pid_t **pids, char ***envp)
{
	int	count;

	count = count_cmds(cmds);
	*pids = malloc(sizeof(pid_t) * count);
	*envp = ft_env_list_to_array(shell->env_list);
	if (!*pids || !*envp)
		ft_error_exit("alloc");
	return (count);
}

int	handle_parent_builtin(t_comnd *cmds, t_shell *shell, char **envp,
		pid_t *pids)
{
	if (is_parent_builtin(cmds))
	{
		shell->last_status = ft_dispatch_builtin_with_arrays(cmds->av_cmd, &shell->env_list,
				shell);
		free_env_array(envp);
		cleanup_all_fds(cmds);
		free(pids);
		return (1);
	}
	return (0);
}

void	setup_pipe(int pfd[2], t_comnd *current)
{
	if (current->next)
	{
		if (pipe(pfd) < 0)
			ft_error_exit("pipe");
	}
	else
	{
		pfd[0] = -1;
		pfd[1] = -1;
	}
}

void	launch_child(t_pipe *ctx)
{
	ctx->pids[ctx->i] = fork();
	if (ctx->pids[ctx->i] < 0)
		ft_error_exit("fork");
	if (ctx->pids[ctx->i] == 0)
		run_child(ctx);
}

void	close_parent_fds(int *prev, int pfd[2])
{
	if (*prev >= 0)
		close(*prev);
	if (pfd[1] >= 0)
		close(pfd[1]);
	*prev = pfd[0];
}
