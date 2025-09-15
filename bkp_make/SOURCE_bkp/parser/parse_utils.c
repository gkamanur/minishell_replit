/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:05:48 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/11 14:03:21 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

void	init_command_args(t_cmd_args *args)
{
	args->capacity = 8;
	args->argc = 0;
	args->argv = malloc(sizeof(char *) * args->capacity);
	 args->arg_tokens = malloc(sizeof(t_token *) * args->capacity);
    if (!args->argv || !args->arg_tokens)
    {
        free(args->argv);
        free(args->arg_tokens);
        args->argv = NULL;
        args->arg_tokens = NULL;
        args->capacity = 0;
        args->argc = 0;
    }
}

void	cleanup_command_parsing(t_cmd_args *args, t_comnd *cmd)
{
	int	i;

    if (args->argv)
    {
        i = 0;
        while (i < args->argc)
        {
            free(args->argv[i]); // free duplicated strings
            i++;
        }
        free(args->argv);
    }
    free(args->arg_tokens);
	ft_free_commands(&cmd);
}

t_comnd	*setup_command_parsing(void)
{
	t_comnd	*cmd;

	cmd = ft_create_command_node();
	if (!cmd)
		return (NULL);
	return (cmd);
}
