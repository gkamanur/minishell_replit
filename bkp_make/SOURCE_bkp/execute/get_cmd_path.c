/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:38:22 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/21 12:02:23 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_put_cmd_not_found(char *cmd, char **cmd_array)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (cmd_array)
		ft_free_strings(cmd_array);
	get_next_line(-1);
	exit(127);
}

char	*ft_create_path(char *cmd, char **dirs)
{
	char	fullpath[PATH_MAX];
	int		i;

	i = 0;
	while (dirs[i])
	{
		ft_strlcpy(fullpath, dirs[i], sizeof(fullpath));
		ft_strlcat(fullpath, "/", sizeof(fullpath));
		ft_strlcat(fullpath, cmd, sizeof(fullpath));
		if (access(fullpath, X_OK) == 0)
			return (ft_strdup(fullpath));
		i++;
	}
	return (NULL);
}

char	*ft_get_path_env(char *var, char **env)
{
	size_t	len;
	int		i;

	if (!var || !env)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*ft_get_cmd_path(char *cmd, char **env)
{
	char	**dirs;
	char	*path_env;
	char	*path_copy;
	char	*fullpath;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = ft_get_path_env("PATH", env);
	if (!path_env)
		return (NULL);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	dirs = ft_split(path_copy, ':');
	free(path_copy);
	if (!dirs)
		return (NULL);
	fullpath = ft_create_path(cmd, dirs);
	ft_free_strings(dirs);
	return (fullpath);
}

void	ft_execve_normal_cmd_array(char **cmd_array, char **env)
{
	char	*fullpath;
	int		i;

	if (!cmd_array || !cmd_array[0])
		ft_put_cmd_not_found("(null)", cmd_array);
	i = 0;
	while (cmd_array[i])
		ft_trim_newline(cmd_array[i++]);
	fullpath = ft_get_cmd_path(cmd_array[0], env);
	if (!fullpath)
		ft_put_cmd_not_found(cmd_array[0], cmd_array);
	execve(fullpath, cmd_array, env);
	ft_put_exec_error(cmd_array[0], cmd_array, fullpath);
}

// void	ft_execve_normal_cmd_array(char **cmd_array, char **env)
// {
// 	char	*fullpath;
// 	int		i;

// 	if (!cmd_array || !cmd_array[0])
// 		ft_put_cmd_not_found("(null)", cmd_array);
// 	i = 0;
// 	while (cmd_array[i])
// 		ft_trim_newline(cmd_array[i++]);
// 	fullpath = ft_get_cmd_path(cmd_array[0], env);
// 	if (!fullpath)
// 		ft_put_cmd_not_found(cmd_array[0], cmd_array);
// 	printf("Exec path: %s\n", fullpath); // Delete when ready
// 	i = 0;
// 	while (cmd_array[i]) // Delete when ready
// 	{
// 		printf("Arg[%d]: %s\n", i, cmd_array[i]);
// 		i++;
// 	}
// 	execve(fullpath, cmd_array, env);
// 	ft_put_exec_error(cmd_array[0], cmd_array, fullpath);
// }
