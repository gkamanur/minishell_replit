/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:23:39 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/15 10:37:50 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_export_name_len(const char *arg)
{
    size_t	i;

    if (!arg)
        return (0);
    i = 0;
    while (arg[i] && arg[i] != '=')
        i++;
    return (i);
}

int	is_valid_export_arg(const char *arg)
{
    size_t	name_len;
    size_t	i;

    if (!arg || !arg[0])
        return (0);
    name_len = ft_export_name_len(arg);
    if (name_len == 0)
        return (0);
    if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
        return (0);
    i = 1;
    while (i < name_len)
    {
        if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

void	print_export_error(const char *name)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(name, 2);
    ft_putendl_fd("': not a valid identifier", 2);
}

void	print_export_list(t_env_var *env_list)
{
	while (env_list)
	{
		if (env_list->envar_name)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env_list->envar_name, 1);
			if (env_list->envar_value)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(env_list->envar_value, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putchar_fd('\n', 1);
		}
		env_list = env_list->next_envar;
	}
}

