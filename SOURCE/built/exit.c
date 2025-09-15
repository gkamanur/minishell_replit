/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:29:12 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/15 10:36:54 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **av_cmd, t_shell *shell)
{
	long	exit_code;

	//printf(RED "\n✅ EXIT ✅\n" RESET);
	if (av_cmd[1])
	{
		if (!is_numeric(av_cmd[1]))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit_code = 2;
		}
		else if (av_cmd[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		else
			exit_code = ft_atoi(av_cmd[1]);
	}
	else
		exit_code = shell->last_status;
	ft_putstr_fd(RED "exit\n" RESET, 1);
	exit(exit_code);
}
