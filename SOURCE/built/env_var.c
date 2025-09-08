/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:22:33 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/20 14:25:11 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_env_value(char *name, t_env_var *env_list)
{
	t_env_var	*tmp;
	size_t		name_len;

	tmp = env_list;
	name_len = ft_strlen(name);
	while (tmp)
	{
		if (ft_strncmp(tmp->envar_name, name, name_len) == 0
			&& tmp->envar_name[name_len] == '\0')
			return (tmp->envar_value);
		tmp = tmp->next_envar;
	}
	return (NULL);
}

int	ft_update_env_var(t_env_var *current, const char *value)
{
	free(current->envar_value);
	if (value)
		current->envar_value = ft_strdup(value);
	else
		current->envar_value = ft_strdup("");
	if (!current->envar_value)
		return (0);
	return (1);
}

int	ft_create_env_var(const char *name, const char *value, t_env_var **env_list)
{
	t_env_var	*new_node;

	new_node = malloc(sizeof(t_env_var));
	if (!new_node)
		return (0);
	new_node->envar_name = ft_strdup(name);
	if (value)
		new_node->envar_value = ft_strdup(value);
	else
		new_node->envar_value = ft_strdup("");
	if (!new_node->envar_name || !new_node->envar_value)
	{
		free(new_node->envar_name);
		free(new_node->envar_value);
		free(new_node);
		return (0);
	}
	new_node->next_envar = *env_list;
	*env_list = new_node;
	return (1);
}

int	ft_set_env_var(const char *name, const char *value, t_env_var **env_list)
{
	t_env_var	*current;

	if (!name || !env_list)
		return (0);
	current = *env_list;
	while (current)
	{
		if (!ft_strcmp(current->envar_name, name))
			return (ft_update_env_var(current, value));
		current = current->next_envar;
	}
	return (ft_create_env_var(name, value, env_list));
}

void	unset_env_variable(const char *name, t_env_var **env_list)
{
	t_env_var	*current;
	t_env_var	*prev;

	if (!name || !env_list || !*env_list)
		return ;
	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->envar_name, name))
		{
			if (prev)
				prev->next_envar = current->next_envar;
			else
				*env_list = current->next_envar;
			free(current->envar_name);
			free(current->envar_value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next_envar;
	}
}
