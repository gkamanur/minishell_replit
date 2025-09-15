/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:27:38 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/15 10:38:32 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_unset_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(char **av_cmd, t_env_var **env_list)
{
	int	status;
	int	i;

	if (!av_cmd[1])
		return (0);
	status = 0;
	i = 1;
	while (av_cmd[i])
	{
		if (is_valid_unset_identifier(av_cmd[i]))
			unset_env_variable(av_cmd[i], env_list);
		else
		{
			ft_putstr_fd("unset: `", 1);
			ft_putstr_fd(av_cmd[i], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			status = 1;
		}
		i++;
	}
	return (status);
}
