/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:53:39 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/21 11:27:22 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_var	*ft_build_env_list(char **env_vars)
{
	t_env_var	*new_node;
	t_env_var	*first;
	t_env_var	*last;
	int			i;

	first = NULL;
	last = NULL;
	i = 0;
	while (env_vars[i])
	{
		new_node = ft_create_env_list(env_vars[i]);
		if (new_node)
		{
			if (!first)
				first = new_node;
			else
				last->next_envar = new_node;
			last = new_node;
		}
		i++;
	}
	return (first);
}
