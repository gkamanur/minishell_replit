/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:47:52 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/25 15:36:33 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_env_node(t_env_var *node)
{
	if (!node)
		return ;
	if (node->envar_name)
		free(node->envar_name);
	if (node->envar_value)
		free(node->envar_value);
	free(node);
}

void	ft_add_back(t_comnd **list, t_comnd *new)
{
	t_comnd	*last;

	if (!list || !new)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_token	*ft_new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->quote = 0;
	token->type = type;
	token->token_value = value;
	token->next_token = NULL;
	return (token);
}

t_comnd	*ft_create_command_node(void)
{
	t_comnd	*command;

	command = malloc(sizeof(t_comnd));
	if (!command)
		return (NULL);
	command->av_cmd = NULL;
	command->infile_name = NULL;
	command->outfile_name = NULL;
	command->delimiter = NULL;
	command->infile = -1;
	command->outfile = -1;
	command->redirec_type = 0;
	command->quote = 0;
	command->next = NULL;
	return (command);
}

t_env_var	*ft_create_env_list(const char *env_line)
{
	t_env_var	*env_node;
	size_t		name_len;
	char		*equal_sign_ptr;

	env_node = malloc(sizeof(t_env_var));
	if (!env_node)
		return (NULL);
	equal_sign_ptr = ft_strchr(env_line, '=');
	if (!equal_sign_ptr)
		return (ft_free_env_node(env_node), NULL);
	name_len = equal_sign_ptr - env_line;
	env_node->envar_name = ft_substr(env_line, 0, name_len);
	if (!env_node->envar_name)
		return (ft_free_env_node(env_node), NULL);
	env_node->envar_value = ft_strdup(equal_sign_ptr + 1);
	if (!env_node->envar_value)
		return (ft_free_env_node(env_node), NULL);
	env_node->next_envar = NULL;
	return (env_node);
}
