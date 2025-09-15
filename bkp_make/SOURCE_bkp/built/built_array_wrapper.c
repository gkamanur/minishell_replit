/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_array_wrapper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:03:00 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/04 10:03:00 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Enhanced builtin dispatcher that handles array variables
 * This wraps the existing export functionality to support arrays
 */
int	ft_dispatch_builtin_with_arrays(char **av_cmd, t_env_var **env_list, t_shell *shell)
{
	int		i;
	int		has_array_syntax;

	if (!av_cmd || !av_cmd[0])
		return (shell->last_status);
	
	// For export command, check if we have array syntax
	if (!ft_strcmp(av_cmd[0], "export"))
	{
		has_array_syntax = 0;
		i = 1;
		while (av_cmd[i])
		{
			if (ft_is_array_assignment(av_cmd[i]))
			{
				has_array_syntax = 1;
				break;
			}
			i++;
		}
		
		if (has_array_syntax)
		{
			// Use array-aware export
			return (ft_builtin_export_with_arrays(av_cmd, env_list, &shell->array_list));
		}
		else
		{
			// Use original export for regular variables
			return (builtin_export(av_cmd, env_list, NULL, NULL));
		}
	}
	
	// For all other commands, use the original dispatcher
	return (ft_dispatch_builtin(av_cmd, env_list, shell));
}

/**
 * Enhanced variable expansion that checks both env and array lists
 * This can be used in the expansion phase
 */
char	*ft_get_expanded_variable_value(const char *name, t_shell *shell)
{
	char	*env_value;
	char	*array_value;

	if (!name || !shell)
		return (NULL);
	
	// First check regular environment variables
	env_value = get_env_value((char *)name, shell->env_list);
	if (env_value)
		return (ft_strdup(env_value));
	
	// Then check array variables (return first element)
	array_value = ft_get_array_first_element(name, shell->array_list);
	if (array_value)
		return (ft_strdup(array_value));
	
	return (NULL);
}

/**
 * Initialize shell with array support
 */
void	ft_init_shell_arrays(t_shell *shell)
{
	if (shell)
		shell->array_list = NULL;
}

/**
 * Clean up shell arrays
 */
void	ft_clean_shell_arrays(t_shell *shell)
{
	if (shell && shell->array_list)
		ft_free_array_list(&shell->array_list);
}
