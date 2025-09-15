/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:46:17 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/10 18:38:10 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


// void sigint_handler(int signo)
// {
//     (void)signo;
    
//     if (g_gb.last_sig == SIGINT_HEREDOC)
//     {
//         write(STDOUT_FILENO, "\n", 1);
//         g_gb.last_sig = SIGINT;
//         return;
//     }
    
//     // Set the signal flag
//     g_gb.last_sig = SIGINT;
    
//     // Interrupt readline by setting done flag and clearing the line
//     write(STDOUT_FILENO, "\n", 1);
//     rl_done = 1;
//     rl_replace_line("", 0);
//     rl_point = rl_end = 0;
    
//     // Wake up readline
//     rl_callback_handler_remove();
// }

void	sigint_handler(int signo)
{
	(void)signo;
	g_gb.last_sig = SIGINT;

	// For heredoc special case
	// if (g_gb.last_sig == SIGINT_HEREDOC) 
	// {
	// 	write(STDOUT_FILENO, "\n", 1);
	// 	return;
	// }

	// Normal input: cancel current line, redisplay prompt
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
     rl_done = 1;
}



void	ft_setup_signals(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}


int handle_nested_minishell(char **argv, char **envp)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return (1);
    }
    if (pid == 0)
    {
        // --- Child process ---
        // Reset signals to defaults
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        // Replace process with a new minishell
        execve(argv[0], argv, envp);

        // If execve fails:
        perror("execve");
        exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            g_gb.last_status_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_gb.last_status_code = 128 + WTERMSIG(status);

        return (g_gb.last_status_code);
    }
}
