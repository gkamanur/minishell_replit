/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:28:22 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/20 14:25:11 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_env(char **av_cmd, t_env_var **env_list)
{
	t_env_var	*current;

	if (av_cmd[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	current = *env_list;
	while (current)
	{
		if (current->envar_name && current->envar_value)
			printf("%s=%s\n", current->envar_name, current->envar_value);
		current = current->next_envar;
	}
	return (0);
}
