/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:03:00 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/04 10:03:00 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Creates a new array variable node
 */
t_array_var	*ft_create_array_node(const char *name)
{
	t_array_var	*new_array;

	if (!name)
		return (NULL);
	new_array = malloc(sizeof(t_array_var));
	if (!new_array)
		return (NULL);
	new_array->array_name = ft_strdup(name);
	if (!new_array->array_name)
	{
		free(new_array);
		return (NULL);
	}
	new_array->elements = NULL;
	new_array->element_count = 0;
	new_array->capacity = 0;
	new_array->next_array = NULL;
	return (new_array);
}

/**
 * Adds an element to an array variable
 */
int	ft_add_array_element(t_array_var *array, const char *element)
{
	char	**new_elements;
	int		new_capacity;
	int		i;

	if (!array || !element)
		return (0);
	if (array->element_count >= array->capacity)
	{
		new_capacity = array->capacity == 0 ? 4 : array->capacity * 2;
		new_elements = malloc(sizeof(char *) * new_capacity);
		if (!new_elements)
			return (0);
		i = 0;
		while (i < array->element_count)
		{
			new_elements[i] = array->elements[i];
			i++;
		}
		free(array->elements);
		array->elements = new_elements;
		array->capacity = new_capacity;
	}
	array->elements[array->element_count] = ft_strdup(element);
	if (!array->elements[array->element_count])
		return (0);
	array->element_count++;
	return (1);
}

/**
 * Finds an array variable by name
 */
t_array_var	*ft_find_array(const char *name, t_array_var *array_list)
{
	t_array_var	*current;

	if (!name)
		return (NULL);
	current = array_list;
	while (current)
	{
		if (ft_strcmp(current->array_name, name) == 0)
			return (current);
		current = current->next_array;
	}
	return (NULL);
}

/**
 * Gets the first element of an array (for simple variable access)
 */
char	*ft_get_array_first_element(const char *name, t_array_var *array_list)
{
	t_array_var	*array;

	array = ft_find_array(name, array_list);
	if (!array || array->element_count == 0)
		return (NULL);
	return (array->elements[0]);
}

/**
 * Frees an array variable and all its elements
 */
void	ft_free_array(t_array_var *array)
{
	int	i;

	if (!array)
		return ;
	free(array->array_name);
	i = 0;
	while (i < array->element_count)
	{
		free(array->elements[i]);
		i++;
	}
	free(array->elements);
	free(array);
}

/**
 * Frees the entire array list
 */
void	ft_free_array_list(t_array_var **array_list)
{
	t_array_var	*current;
	t_array_var	*next;

	if (!array_list)
		return ;
	current = *array_list;
	while (current)
	{
		next = current->next_array;
		ft_free_array(current);
		current = next;
	}
	*array_list = NULL;
}
