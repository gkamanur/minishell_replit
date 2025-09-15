/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:03:00 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/04 10:03:00 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Gets variable value from either env_list or array_list
 */
char	*ft_get_variable_value(const char *name, t_env_var *env_list, t_array_var *array_list)
{
	char	*env_value;
	char	*array_value;

	if (!name)
		return (NULL);
	
	// First check regular environment variables
	env_value = get_env_value((char *)name, env_list);
	if (env_value)
		return (env_value);
	
	// Then check array variables (return first element)
	array_value = ft_get_array_first_element(name, array_list);
	return (array_value);
}

/**
 * Enhanced builtin_export that handles both regular and array variables
 */
int	ft_builtin_export_with_arrays(char **av_cmd, t_env_var **env_list, t_array_var **array_list)
{
	int		i;
	char	*arg;
	char	*equals;
	char	*name;

	if (!av_cmd[1])
	{
		print_export_list(*env_list);
		return (0);
	}
	
	i = 1;
	while (av_cmd && av_cmd[i])
	{
		arg = av_cmd[i];
		equals = ft_strchr(arg, '=');
		
		if (!is_valid_export_arg(arg))
		{
			print_export_error(arg);
			i++;
			continue;
		}
		
		if (equals)
		{
			name = ft_substr(arg, 0, equals - arg);
			if (!name)
			{
				i++;
				continue;
			}
			
			// Check if it's an array assignment
			if (ft_is_array_assignment(arg))
			{
				// Remove from regular env vars if it exists
				unset_env_variable(name, env_list);
				// Set as array variable
				ft_set_array_var(name, equals + 1, array_list);
			}
			else
			{
				// Remove from arrays if it exists
				ft_remove_array(name, array_list);
				// Set as regular variable
				ft_set_env_var(name, equals + 1, env_list);
			}
			free(name);
		}
		else
		{
			// Variable without assignment - create empty if doesn't exist
			if (!get_env_value(arg, *env_list) && !ft_find_array(arg, *array_list))
				ft_set_env_var(arg, "", env_list);
		}
		
		i++;
	}
	
	return (0);
}
