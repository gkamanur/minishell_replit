/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:25:09 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/28 15:27:47 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_cd_arg_has_ws(char *path)
{
	int	i;

	if (!path)
		return (0);
	i = 0;
	while (path[i])
	{
		if (path[i] == ' ' || path[i] == '\t' || path[i] == '\n')
		{
			ft_putstr_fd("cd: too many arguments\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_get_cd(char **av_cmd, t_env_var **env_list)
{
	char	*path;

	if (!av_cmd[1])
	{
		path = get_env_value("HOME", *env_list);
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		return (path);
	}
	if (av_cmd[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), NULL);
	path = av_cmd[1];
	if (!ft_strcmp(path, "-"))
	{
		path = get_env_value("OLDPWD", *env_list);
		if (!path)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), NULL);
		printf("%s\n", path);
	}
	if (ft_cd_arg_has_ws(path))
		return (NULL);
	return (path);
}

int	builtin_cd(char **av_cmd, t_env_var **env_list)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*path;

	path = ft_get_cd(av_cmd, env_list);
	if (!path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd: getcwd"), 1);
	if (chdir(path) != 0)
		return (perror("cd"), free(old_pwd), 1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (perror("cd: getcwd"), free(old_pwd), 1);
	if (!ft_set_env_var("OLDPWD", old_pwd, env_list)
		|| !ft_set_env_var("PWD", new_pwd, env_list))
	{
		free(old_pwd);
		free(new_pwd);
		return (1);
	}
	free(old_pwd);
	free(new_pwd);
	return (0);
}
