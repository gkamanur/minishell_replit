/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:25:57 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/20 14:25:11 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_pwd(char **av_cmd, t_env_var **env_list)
{
	char	current_wdir[PATH_MAX];

	(void)av_cmd;
	(void)env_list;
	if (getcwd(current_wdir, sizeof(current_wdir)) != NULL)
	{
		printf("%s\n", current_wdir);
		return (0);
	}
	perror("pwd");
	return (1);
}
