/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:31:53 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/20 14:25:11 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	ft_trim_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == ' '
			|| str[len - 1] == '\t'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

int	free_partial_envp(char **envp, int i)
{
	while (i > 0)
		free(envp[--i]);
	return (0);
}

int	fill_envp_array(char **envp, t_env_var *env_list)
{
	char	*tmp_str;
	int		i;

	i = 0;
	while (env_list)
	{
		tmp_str = ft_strjoin(env_list->envar_name, "=");
		if (!tmp_str)
			return (free_partial_envp(envp, i));
		envp[i] = ft_strjoin(tmp_str, env_list->envar_value);
		free(tmp_str);
		if (!envp[i])
			return (free_partial_envp(envp, i));
		i++;
		env_list = env_list->next_envar;
	}
	envp[i] = NULL;
	return (1);
}

char	**ft_env_list_to_array(t_env_var *env_list)
{
	t_env_var	*tmp;
	char		**envp;
	int			count;

	count = 0;
	tmp = env_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next_envar;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	if (!fill_envp_array(envp, env_list))
	{
		free(envp);
		return (NULL);
	}
	return (envp);
}
