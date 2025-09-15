/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:55:50 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/15 10:39:16 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Add to SOURCE/execute/command.c
// Add to SOURCE/execute/command.c
void	ft_put_syntax_error(const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

void	ft_put_bash_error(const char *command, const char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_put_bash_error_with_arg(const char *command, const char *arg, const char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

// void	exec_command(t_comnd *current, char **envp)
// {
// 	char	*fullpath;

// 	if (current->av_cmd && current->av_cmd[0])
// 	{
// 		fullpath = ft_get_cmd_path(current->av_cmd[0], envp);
// 		if (!fullpath)
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(current->av_cmd[0], 2);
// 			ft_putstr_fd(": command not found\n", 2);
// 			exit(127); // Command not found
// 		}
// 		// printf("print :%s \n",fullpath);
// 		// for (int i = 0; current->av_cmd[i]; i++)
//     	// 	fprintf(stderr, "argv[%d] = [%s]\n", i, current->av_cmd[i]);
// 		execve(fullpath, current->av_cmd, envp);
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(current->av_cmd[0], 2);
// 		ft_putstr_fd(": ", 2);
// 		ft_putstr_fd(strerror(errno), 2);
// 		ft_putstr_fd("\n", 2);
// 		free(fullpath);
// 		exit(126); // Permission denied/execve failure
// 	}
// 	exit(127); // No command
// }
void exec_command(t_comnd *current, char **envp)
{
    char *fullpath;

    if (!current || !current->av_cmd || !current->av_cmd[0])
        exit(127); // No command

    // Find full path
    fullpath = ft_get_cmd_path(current->av_cmd[0], envp);
    if (!fullpath)
    {
        // Command not found
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(current->av_cmd[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }

    // Execute the command
    execve(fullpath, current->av_cmd, envp);

    // If execve returns, it failed
    perror(current->av_cmd[0]); // prints exactly one error, e.g. "cat: minishell.h: No such file or directory"
    free(fullpath);
    exit(126); // execve failed
}

void	fork_and_exec(t_comnd *curre, int prev_fd, int pipe_fd[2], char **envp)
{
	pid_t	pid;

	pid = fork();
	ft_check_fork(pid);
	if (pid == 0)
	{
		if (pipe_fd != NULL)
		{
			close(pipe_fd[0]);
			ft_child_setup(curre, prev_fd, pipe_fd[1]);
		}
		else
			ft_child_setup(curre, prev_fd, -1);
		exec_command(curre, envp);
	}
}

void	ft_parent_cleanup(int *prev_fd, int pipe_fd[2])
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (pipe_fd && pipe_fd[1] != -1)
	{
		close(pipe_fd[1]);
		pipe_fd[1] = -1;
	}
}

// #ifdef DEBUG
// void	print_commands(t_comnd *cmds)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (cmds)
// 	{
// 		printf("Command %d:\n", i);
// 		if (cmds->av_cmd)
// 		{
// 			j = 0;
// 			while (cmds->av_cmd[j])
// 			{
// 				printf("  argv[%d]: %s\n", j, cmds->av_cmd[j]);
// 				j++;
// 			}
// 		}
// 		if (cmds->infile_name)
// 			printf("  infile: %s\n", cmds->infile_name);
// 		if (cmds->outfile_name)
// 			printf("  outfile: %s\n", cmds->outfile_name);
// 		if (cmds->delimiter)
// 			printf("  heredoc delimiter: %s\n", cmds->delimiter);
// 		cmds = cmds->next;
// 		i++;
// 	}
// }
// #endif
