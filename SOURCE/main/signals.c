/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:46:17 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/08 16:32:20 by gkamanur         ###   ########.fr       */
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
	if ( g_gb.last_sig == SIGINT_HEREDOC)
	{
		write(STDOUT_FILENO, "\n", 1);
		 g_gb.last_sig = SIGINT;
	}
	else
	{
		 g_gb.last_sig = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	ft_setup_signals(void)
// {
// 	struct sigaction	sa;

// 	// Use our signal handling but let readline manage display
// 	rl_catch_signals = 1;
// 	rl_catch_sigwinch = 1;
	
// 	sa.sa_handler = sigint_handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0; // Remove SA_RESTART for immediate interruption
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	ft_setup_signals(void)
{
	struct sigaction	sa;

	rl_catch_signals = 1;
	rl_catch_sigwinch = 1;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
