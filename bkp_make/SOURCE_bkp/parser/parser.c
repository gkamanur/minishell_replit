/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:08:47 by robello           #+#    #+#             */
/*   Updated: 2025/09/11 14:54:20 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Add to SOURCE/parser/parser.c
int	ft_check_syntax_errors(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return (0);
	
	current = tokens;
	
	// Check for leading pipe
	if (current->type == TOKEN_PIPE)
		return (1);
	
	while (current)
	{
		next = current->next_token;
		
		// Check for consecutive pipes
		if (current->type == TOKEN_PIPE && next && next->type == TOKEN_PIPE)
			return (1);
		
		// Check for trailing pipe
		if (current->type == TOKEN_PIPE && !next)
			return (1);
		
		// Check for redirect without filename
		if ((current->type == TOKEN_REDIRECT_IN || 
			 current->type == TOKEN_REDIRECT_OUT ||
			 current->type == TOKEN_HEREDOC ||
			 current->type == TOKEN_APPEND) && 
			(!next || next->type != TOKEN_WORD))
			return (1);
		
		// Check for consecutive redirects
		if ((current->type == TOKEN_REDIRECT_IN || 
			 current->type == TOKEN_REDIRECT_OUT ||
			 current->type == TOKEN_HEREDOC ||
			 current->type == TOKEN_APPEND) && 
			next && (next->type == TOKEN_REDIRECT_IN || 
					next->type == TOKEN_REDIRECT_OUT ||
					next->type == TOKEN_HEREDOC ||
					next->type == TOKEN_APPEND))
			return (1);
		
		current = next;
	}
	return (0);
}

void	ft_handle_syntax_error(t_shell *shell, const char *error_msg)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("'\n", 2);
	shell->last_status = 2;
}
static t_token *build_token_list_from_args(t_cmd_args *args)
{
    t_token *head = NULL;
    t_token *prev = NULL;
    int     i;

    i = 0;
    while (i < args->argc)
    {
        if (!head)
            head = args->arg_tokens[i];
        else
            prev->next_token = args->arg_tokens[i];
        prev = args->arg_tokens[i];
        i++;
    }
    if (prev)
        prev->next_token = NULL;
    return head;
}
t_comnd	*ft_parse_command(t_token **tok_ptr)
{
	t_comnd		*cmd;
	t_cmd_args	args;
	int			res;

	cmd = setup_command_parsing();
	if (!cmd)
		return (NULL);
	init_command_args(&args);
	if (!args.argv || !args.arg_tokens)
		return (ft_free_commands(&cmd), NULL);
	while (*tok_ptr && (*tok_ptr)->type != TOKEN_PIPE)
	{
		res = process_token(tok_ptr, cmd, &args);
			
		if (res <= 0)
		{
			if (res < 0)
				cleanup_command_parsing(&args, cmd);
			else
			{
                // partial cleanup if add_argument failed before any tokens were duplicated
                if (args.argv)
                {
                    int i = 0;
                    while (i < args.argc)
                        free(args.argv[i++]);
                    free(args.argv);
                }
                free(args.arg_tokens);
                ft_free_commands(&cmd);
            }
			return (NULL);
		}
	}
	args.argv[args.argc] = NULL;
	cmd->av_cmd = args.argv;
	cmd->av_cmd_lst = build_token_list_from_args(&args);
	free(args.arg_tokens);
	return (cmd);
}

t_comnd	*ft_build_cmdline(t_comnd **first, t_comnd **last, t_token **current)
{
	t_comnd	*cmd;

	cmd = ft_parse_command(current);
	if (!cmd)
		return (NULL);
	if (!*first)
	{
		*first = cmd;
		*last = cmd;
	}
	else
	{
		(*last)->next = cmd;
		*last = cmd;
	}
	return (*last);
}

t_token	*handle_pipe_token(t_token *current)
{
	if (current && current->type == TOKEN_PIPE)
		return (current->next_token);
	else if (current)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		g_gb.last_status_code = 2;
		return (NULL);
	}
	return (current);
}

int	ft_validate_redirect_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next_token;
		
		// Check for redirect without filename
		if ((current->type == TOKEN_REDIRECT_IN || 
			 current->type == TOKEN_REDIRECT_OUT ||
			 current->type == TOKEN_HEREDOC ||
			 current->type == TOKEN_APPEND) && 
			(!next || next->type != TOKEN_WORD))
		{
			if (current->type == TOKEN_REDIRECT_OUT)
			{
				if (!next)
					ft_put_syntax_error("newline");
				else
					ft_put_syntax_error(">");
			}
			else if (current->type == TOKEN_REDIRECT_IN)
			{
				if (!next)
					ft_put_syntax_error("newline");
				else
					ft_put_syntax_error("<");
			}
			else if (current->type == TOKEN_HEREDOC)
			{
				if (!next)
					ft_put_syntax_error("newline");
				else
					ft_put_syntax_error("<<");
			}
			else if (current->type == TOKEN_APPEND)
			{
				if (!next)
					ft_put_syntax_error("newline");
				else if (next->type == TOKEN_REDIRECT_OUT)
					ft_put_syntax_error(">");
				else
					ft_put_syntax_error(">>");
			}
			return (1);
		}
		
		// Check for consecutive redirects
		if ((current->type == TOKEN_REDIRECT_IN || 
			 current->type == TOKEN_REDIRECT_OUT ||
			 current->type == TOKEN_HEREDOC ||
			 current->type == TOKEN_APPEND) && 
			next && (next->type == TOKEN_REDIRECT_IN || 
					next->type == TOKEN_REDIRECT_OUT ||
					next->type == TOKEN_HEREDOC ||
					next->type == TOKEN_APPEND))
		{
			if (next->type == '\n')
				ft_put_syntax_error("newline");
			if (next->type == TOKEN_REDIRECT_OUT)
				ft_put_syntax_error(">");
			else if (next->type == TOKEN_REDIRECT_IN)
				ft_put_syntax_error("<");
			else if (next->type == TOKEN_HEREDOC)
				ft_put_syntax_error("<<");
			else if (next->type == TOKEN_APPEND)
				ft_put_syntax_error(">>");
			return (1);
		}
		
		current = next;
	}
	return (0);
}

int	ft_validate_pipe_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return (0);
	
	current = tokens;
	
	// Check for leading pipe
	if (current->type == TOKEN_PIPE)
	{
		ft_put_syntax_error("|");
		return (1);
	}
	
	while (current)
	{
		next = current->next_token;
		
		// Check for consecutive pipes
		if (current->type == TOKEN_PIPE && next && next->type == TOKEN_PIPE)
		{
			ft_put_syntax_error("|");
			return (1);
		}
		
		// Check for trailing pipe
		if (current->type == TOKEN_PIPE && !next)
		{
			ft_put_syntax_error("|");
			return (1);
		}
		
		current = next;
	}
	return (0);
}

t_comnd	*ft_parser_main(t_token *tokens)
{
	t_comnd	*first;
	t_comnd	*last;
	t_token	*current;

	first = NULL;
	last = NULL;
	current = tokens;

	if (ft_validate_pipe_syntax(tokens) || ft_validate_redirect_syntax(tokens))
	{
		// Exit code 2 is already set by the validation functions
		return (NULL);
	}
	while (current)
	{
		last = ft_build_cmdline(&first, &last, &current);
		if (!last)
		{
			ft_free_commands(&first);
			g_gb.last_status_code = 2;
			return (NULL);
		}
		current = handle_pipe_token(current);
	}
	return (first);
}
