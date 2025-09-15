/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:03:00 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/04 10:03:00 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Checks if a string contains array syntax VAR=(...)
 */
int	ft_is_array_assignment(const char *arg)
{
	char	*equals;
	char	*open_paren;

	if (!arg)
		return (0);
	equals = ft_strchr(arg, '=');
	if (!equals)
		return (0);
	open_paren = ft_strchr(equals + 1, '(');
	if (!open_paren)
		return (0);
	// Check if there's a closing parenthesis
	if (!ft_strchr(open_paren, ')'))
		return (0);
	return (1);
}

/**
 * Extracts variable name from array assignment
 */
char	*ft_extract_array_name(const char *arg)
{
	char	*equals;

	if (!arg)
		return (NULL);
	equals = ft_strchr(arg, '=');
	if (!equals)
		return (NULL);
	return (ft_substr(arg, 0, equals - arg));
}

/**
 * Parses array elements from the parentheses content
 */
static char	**ft_parse_array_elements(const char *content, int *count)
{
	char	**elements;
	int		i;
	int		start;
	int		in_quotes;
	int		element_count;
	char	*current_element;

	if (!content || !count)
		return (NULL);
	*count = 0;
	elements = malloc(sizeof(char *) * 64); // Initial capacity
	if (!elements)
		return (NULL);
	i = 0;
	element_count = 0;
	in_quotes = 0;
	start = 0;
	
	// Skip leading whitespace
	while (content[i] && ft_is_space(content[i]))
		i++;
	start = i;
	
	while (content[i])
	{
		if (content[i] == '"' || content[i] == '\'')
			in_quotes = !in_quotes;
		else if (!in_quotes && ft_is_space(content[i]))
		{
			if (i > start)
			{
				current_element = ft_substr(content, start, i - start);
				if (current_element)
				{
					elements[element_count] = current_element;
					element_count++;
				}
			}
			// Skip whitespace
			while (content[i] && ft_is_space(content[i]))
				i++;
			start = i;
			continue;
		}
		i++;
	}
	
	// Handle last element
	if (i > start)
	{
		current_element = ft_substr(content, start, i - start);
		if (current_element)
		{
			elements[element_count] = current_element;
			element_count++;
		}
	}
	
	*count = element_count;
	return (elements);
}

/**
 * Creates or updates an array variable from assignment
 */
int	ft_set_array_var(const char *name, const char *value, t_array_var **array_list)
{
	t_array_var	*existing_array;
	t_array_var	*new_array;
	char		*content;
	char		*open_paren;
	char		*close_paren;
	char		**elements;
	int			element_count;
	int			i;

	if (!name || !value || !array_list)
		return (0);
	
	// Extract content between parentheses
	open_paren = ft_strchr(value, '(');
	if (!open_paren)
		return (0);
	close_paren = ft_strrchr(value, ')');
	if (!close_paren || close_paren <= open_paren)
		return (0);
	
	content = ft_substr(value, open_paren + 1 - value, close_paren - open_paren - 1);
	if (!content)
		return (0);
	
	// Remove existing array if it exists
	existing_array = ft_find_array(name, *array_list);
	if (existing_array)
	{
		ft_remove_array(name, array_list);
	}
	
	// Create new array
	new_array = ft_create_array_node(name);
	if (!new_array)
	{
		free(content);
		return (0);
	}
	
	// Parse elements
	elements = ft_parse_array_elements(content, &element_count);
	free(content);
	
	if (!elements && element_count > 0)
	{
		ft_free_array(new_array);
		return (0);
	}
	
	// Add elements to array
	i = 0;
	while (i < element_count)
	{
		if (!ft_add_array_element(new_array, elements[i]))
		{
			// Clean up on failure
			while (i >= 0)
			{
				free(elements[i]);
				i--;
			}
			free(elements);
			ft_free_array(new_array);
			return (0);
		}
		free(elements[i]);
		i++;
	}
	free(elements);
	
	// Add to array list
	new_array->next_array = *array_list;
	*array_list = new_array;
	
	return (1);
}

/**
 * Removes an array from the array list
 */
void	ft_remove_array(const char *name, t_array_var **array_list)
{
	t_array_var	*current;
	t_array_var	*prev;

	if (!name || !array_list || !*array_list)
		return ;
	
	current = *array_list;
	prev = NULL;
	
	while (current)
	{
		if (ft_strcmp(current->array_name, name) == 0)
		{
			if (prev)
				prev->next_array = current->next_array;
			else
				*array_list = current->next_array;
			ft_free_array(current);
			return ;
		}
		prev = current;
		current = current->next_array;
	}
}
