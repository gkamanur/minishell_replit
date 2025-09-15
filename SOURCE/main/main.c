/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:07:32 by robello           #+#    #+#             */
/*   Updated: 2025/09/15 12:15:27 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_gb g_gb = {0, 0};

// Add to SOURCE/main/main.c
int	ft_handle_parsing_error(t_token *tokens, char *input_line, t_shell *shell)
{
	if (tokens)
		free_tokens(tokens);
	if (input_line)
		free(input_line);
	shell->last_status = 2; // Syntax error
	return (0);
}

// Add to SOURCE/main/main.c
void	ft_update_signal_exit_codes(t_shell *shell)
{
	if (g_gb.last_sig == SIGINT)
	{
		shell->last_status = 130;
		g_gb.last_status_code = 130;
	}
	else if (g_gb.last_sig == SIGQUIT)
	{
		shell->last_status = 131;
		g_gb.last_status_code = 131;
	}
}

t_shell	*ft_init_shell(void)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env_list = NULL;
	shell->cmd_list = NULL;
	shell->array_list = NULL;
	shell->last_status = 0;
	return (shell);
}

t_shell	*ft_shell_setup(char **env_vars)
{
	t_shell	*shell;

	shell = ft_init_shell();
	if (!shell)
		return (NULL);
	shell->envp = env_vars;
	shell->env_list = ft_build_env_list(env_vars);
	return (shell);
}

int	ft_manage_inputline(char *input_line, t_shell *shell)
{
	t_token	*tokens;

	if (!input_line)
		return (1);
	if (*input_line)
	{
		add_history(input_line);
		shell->line_cnt++;
	}
	ft_trim_newline(input_line);
	// Reset global status before parsing
	g_gb.last_status_code = 0;
	tokens = ft_lexer_main(input_line);
	if (!tokens)
		return (free(input_line), 0);
	//quotes_tokens(tokens);
	//print_tokens(tokens);
	shell->cmd_list = ft_parser_main(tokens);
	//print_command_list(shell->cmd_list); // Debugging line to print commands
	free_tokens(tokens);
	free(input_line);
	if (!shell->cmd_list)
	{
		// Check if it's a redirection error (exit code 1) or syntax error (exit code 2)
		if (g_gb.last_status_code == 1)
			shell->last_status = 1; // Redirection error
		else
			shell->last_status = 2; // Syntax error
		return (0);
	}
	ft_expand_cmds(shell->cmd_list, shell);
	ft_start_execution(shell->cmd_list, shell);
	ft_free_commands(&shell->cmd_list);
	return (0);
}

void	master_shell_loop(t_shell *shell)
{
	char	*prompt_line;
	char	*input_line;
	int loop;
	int is_interactive;
	
	loop = 0;
	is_interactive = isatty(STDIN_FILENO);
	while (!loop)
	{
		// Reset signal before each prompt
		g_gb.last_sig = 0;
		
		if (is_interactive)
		{
			prompt_line = ft_build_prompt();
			if (!prompt_line)
				continue ;
		}
		else
			prompt_line = NULL;
		
		input_line = read_input_with_quotes(prompt_line, "> ");
		if (prompt_line)
			free(prompt_line);
		
		// Handle SIGINT or NULL input
		
		if (g_gb.last_sig == SIGINT)
		{
		    free(input_line);
		    continue;
		}
		
		// EOF → exit shell
		if (!input_line)
		{
			// Only print EOF in interactive mode
			if (is_interactive)
				ft_putstr_fd(RED "exit\n" RESET, 1);
		    break;
		}
		// Process the complete input line
		loop = ft_manage_inputline(input_line, shell);
		g_gb.last_status_code = shell->last_status;
		ft_update_signal_exit_codes(shell);
	}
}

int	main(int ac, char **av, char **env_vars)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	ft_setup_signals();
	
	shell = ft_shell_setup(env_vars);
	if (!shell)
		exit(EXIT_FAILURE);
	master_shell_loop(shell);
	rl_clear_history();
	ft_clean_shell_setup(shell);
	return (g_gb.last_status_code);
}
