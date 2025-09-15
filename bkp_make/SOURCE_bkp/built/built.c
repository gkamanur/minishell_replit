/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 08:04:25 by robello           #+#    #+#             */
/*   Updated: 2025/08/28 14:56:01 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin_argv(char **av_cmd)
{
	if (!av_cmd || !av_cmd[0])
		return (0);
	return (!ft_strcmp(av_cmd[0], "echo") || !ft_strcmp(av_cmd[0], "cd")
		|| !ft_strcmp(av_cmd[0], "pwd") || !ft_strcmp(av_cmd[0], "export")
		|| !ft_strcmp(av_cmd[0], "unset") || !ft_strcmp(av_cmd[0], "env")
		|| !ft_strcmp(av_cmd[0], "exit"));
}

int	ft_dispatch_builtin(char **av_cmd, t_env_var **env_list, t_shell *shell)
{
	if (!av_cmd || !av_cmd[0])
		return (shell->last_status);
	if (!ft_strcmp(av_cmd[0], "echo"))
		return (builtin_echo(av_cmd, env_list));
	else if (!ft_strcmp(av_cmd[0], "cd"))
		return (builtin_cd(av_cmd, env_list));
	else if (!ft_strcmp(av_cmd[0], "pwd"))
		return (builtin_pwd(av_cmd, env_list));
	else if (!ft_strcmp(av_cmd[0], "export"))
		return (builtin_export(av_cmd, env_list, NULL, NULL));
	else if (!ft_strcmp(av_cmd[0], "unset"))
		return (builtin_unset(av_cmd, env_list));
	else if (!ft_strcmp(av_cmd[0], "env"))
		return (builtin_env(av_cmd, env_list));
	else if (!ft_strcmp(av_cmd[0], "exit"))
		return (builtin_exit(av_cmd, shell));
	return (shell->last_status);
}
