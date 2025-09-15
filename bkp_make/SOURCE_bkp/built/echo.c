/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:23:23 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/25 13:40:58 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_echo(char **av_cmd, t_env_var **env_list)
{
	int	newline;
	int	i;

	(void)env_list;
	newline = 1;
	i = 1;
	if (av_cmd[1] && !ft_strcmp(av_cmd[1], "-n"))
	{
		newline = 0;
		i = 2;
	}
	while (av_cmd[i])
	{
		ft_putstr_fd(av_cmd[i], 1);
		if (av_cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

// int	cell_echo(char **args)
// {
// 	int start = 1;
// 	bool newline = true;

// 	if (!args || !args[0])
// 		return (1);

// 	// Check for the -n option
// 	if (args[1] && !strcmp(args[1], "-n"))
// 	{
// 		newline = false;
// 		start = 2;
// 	}

// 	// Print each argument separated by a space
// 	for (int i = start; args[i]; i++)
// 	{
// 		p("%s", args[i]);
// 		if (args[i + 1])
// 			p(" ");
// 	}

// 	// Print newline if -n option is not present
// 	if (newline)
// 		p("\n");

// 	return (0);
// }