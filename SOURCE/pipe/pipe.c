/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:53:50 by robello           #+#    #+#             */
/*   Updated: 2025/09/15 11:58:03 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_infile_silent(t_comnd *cmd)
{
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = open(cmd->infile_name, O_RDONLY);
	// Don't print any error messages, just set infile = -1 if it fails
	if (cmd->infile < 0)
		cmd->infile = -1;
}

static void	execute_pipeline_loop(t_comnd *cmds, t_shell *shell, pid_t *pids,
		char **envp)
{
	t_pipe	ctx;
	int status;

	(void)status;
	ctx.cmd = cmds;
	ctx.shell = shell;
	ctx.pids = pids;
	ctx.prev = -1;
	ctx.i = 0;
	ctx.envp = envp;

	ft_open_main(ctx.cmd, 0);
	while (ctx.cmd)
	{
		setup_pipe(ctx.pfd, ctx.cmd);
		launch_child(&ctx);
		close_parent_fds(&ctx.prev, ctx.pfd);
		ctx.cmd = ctx.cmd->next;
		ctx.i++;
	}
	ft_wait_all(pids, ctx.i, shell);
}



//#ifdef DEBUG
void    print_command(const t_comnd *cmd)
{
    int i;

    if (!cmd)
    {
        printf("Command: (null)\n");
        return;
    }

    printf("=== Command ===\n");

    // Print argv
    if (cmd->av_cmd)
    {
        i = 0;
        while (cmd->av_cmd[i])
        {
            printf("  av_cmd[%d] = [%s]\n", i, cmd->av_cmd[i]);
            i++;
        }
    }
    else
        printf("  av_cmd = (null)\n");

    // Print file names
    printf("  infile_name   = [%s]\n", cmd->infile_name ? cmd->infile_name : "(null)");
    printf("  outfile_name  = [%s]\n", cmd->outfile_name ? cmd->outfile_name : "(null)");
    printf("  delimiter     = [%s]\n", cmd->delimiter ? cmd->delimiter : "(null)");

    // Print file descriptors and flags
    printf("  infile        = %d\n", cmd->infile);
    printf("  outfile       = %d\n", cmd->outfile);
    printf("  redirec_type  = %d\n", cmd->redirec_type);
    printf("  quote         = %d\n", cmd->quote);

    // Pointer to next command
    printf("  next          = %p\n", (void*)cmd->next);
    printf("================\n");
}
void print_command_list(const t_comnd *cmd)
{
    int i = 1;
    while (cmd)
    {
        printf("\n--- Command #%d ---\n", i);
        print_command(cmd);              // show argv / redirs
        print_tokens(cmd->av_cmd_lst);   // show token list

        cmd = cmd->next;  // ✅ advance to next command
        i++;
    }
}
//#endif

void	ft_pipe_up_bonus(t_comnd *cmds, t_shell *shell)
{
	pid_t	*pids;
	char	**envp;
	int		count;

    (void)count;
	count = setup_allocations(cmds, shell, &pids, &envp);
	if (handle_parent_builtin(cmds, shell, envp, pids))
		return ;
	execute_pipeline_loop(cmds, shell, pids, envp);
	cleanup_all_fds(cmds);
	free_env_array(envp);
	free(pids);
}
