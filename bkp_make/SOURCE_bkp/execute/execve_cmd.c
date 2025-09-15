/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:39:45 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/20 14:25:11 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execve_cmd_flat(char **av_cmd, t_env_var *env_list)
{
	char	**envp;

	envp = ft_env_list_to_array(env_list);
	if (!envp)
		exit(EXIT_FAILURE);
	ft_execve_cmd(av_cmd, envp);
	free_env_array(envp);
}

void	ft_execve_shell_cmd(char *cmd_str, char **env)
{
	char	*argv[4];

	argv[0] = "/bin/sh";
	argv[1] = "-c";
	argv[2] = cmd_str;
	argv[3] = NULL;
	execve(argv[0], argv, env);
	ft_putstr_fd("minishell: line 1: ", 2);
	ft_putstr_fd(cmd_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	get_next_line(-1);
	exit(EXIT_FAILURE);
}

void	ft_execve_cmd(char **av_cmd, char **env)
{
	char	*command_line;
	int		i;

	if (!av_cmd || !av_cmd[0])
	{
		ft_putstr_fd("minishell: command not found: (empty)\n", 2);
		get_next_line(-1);
		exit(127);
	}
	i = 0;
	while (av_cmd[i])
	{
		if (ft_strchr(av_cmd[i], '\'') || ft_strchr(av_cmd[i], '"')
			|| ft_strchr(av_cmd[i], '\\') || ft_strchr(av_cmd[i], '$')
			|| ft_strchr(av_cmd[i], '*') || ft_strchr(av_cmd[i], '`'))
		{
			command_line = ft_join_arguments(av_cmd);
			ft_execve_shell_cmd(command_line, env);
			free(command_line);
			return ;
		}
		i++;
	}
	ft_execve_normal_cmd_array(av_cmd, env);
}
