/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:45:33 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/11 14:20:32 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_clean_shell_setup(t_shell *shell)
{
	if (!shell)
		return ;
	ft_free_env_list(&shell->env_list);
	ft_free_commands(&shell->cmd_list);
	free(shell);
}

void	ft_free_env_list(t_env_var **env_list)
{
	t_env_var	*tmp;
	t_env_var	*current;

	if (!env_list || !*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		tmp = current->next_envar;
		if (current->envar_name)
			free(current->envar_name);
		if (current->envar_value)
			free(current->envar_value);
		free(current);
		current = tmp;
	}
	*env_list = NULL;
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next_token;
		if (tokens->token_value)
			free(tokens->token_value);
		free(tokens);
		tokens = tmp;
	}
}

void	ft_free_command_redirn_fds(t_comnd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->infile_name)
	{
		free(cmd->infile_name);
		cmd->infile_name = NULL;
	}
	if (cmd->outfile_name)
	{
		free(cmd->outfile_name);
		cmd->outfile_name = NULL;
	}
	if (cmd->delimiter)
	{
		free(cmd->delimiter);
		cmd->delimiter = NULL;
	}
}

void	ft_free_commands(t_comnd **cmd_list)
{
	t_comnd	*tmp;
	t_comnd	*current;
	int		i;


	if (!cmd_list || !*cmd_list)
		return ;

	current = *cmd_list;
	while (current)
	{
		tmp = current->next;

		// free argv (string array)
		if (current->av_cmd)
		{
			i = 0;
			while (current->av_cmd[i])
				free(current->av_cmd[i++]);
			free(current->av_cmd);
		}

#ifdef OWN_DUP_TOKENS
		t_token *cur;
		t_token *next;
		cur = current->av_cmd_lst;
		while (cur)
		{
			next = cur->next_token;
			free(cur->token_value);
			free(cur);
			cur = next;
		}
#endif

		// free redirection names
		ft_free_command_redirn_fds(current);

		free(current);
		current = tmp;
	}
	*cmd_list = NULL;
}

