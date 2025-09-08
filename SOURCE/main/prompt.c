/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:54:55 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/27 12:05:08 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_show_home(const char *cwd)
{
	size_t	len;
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (ft_strdup(cwd));
	len = 0;
	while (home[len] && cwd[len] && home[len] == cwd[len])
		len++;
	if (len > 0)
		return (ft_strjoin("~", cwd + len));
	return (ft_strdup(cwd));
}

char	*ft_edit_hostname(const char *hostname)
{
	size_t	i;
	char	*new_name;

	if (!hostname)
		return (ft_strdup("unknown"));
	i = 0;
	while (hostname[i] && hostname[i] != '.')
		i++;
	new_name = ft_substr(hostname, 0, i);
	if (!new_name)
		return (NULL);
	return (new_name);
}

char	*ft_prompt_userhost(const char *user, const char *hostname)
{
	char	*joined;
	char	*host;
	char	*tmp;

	host = ft_edit_hostname(hostname);
	if (!host)
		return (NULL);
	joined = ft_strjoin(COLOR_USERHOST, user);
	if (!joined)
		return (free(host), NULL);
	tmp = ft_strjoin(joined, "@");
	free(joined);
	if (!tmp)
		return (free(host), NULL);
	joined = ft_strjoin(tmp, host);
	free(tmp);
	free(host);
	if (!joined)
		return (NULL);
	tmp = ft_strjoin(joined, COLOR_SHELL " minishell>");
	free(joined);
	return (tmp);
}

char	*ft_prompt_path(char *user_host, const char *cwd)
{
	char	*prompt_path;
	char	*joined;
	char	*tmp;

	if (!user_host)
		return (NULL);
	prompt_path = ft_show_home(cwd);
	if (!prompt_path)
		return (free(user_host), NULL);
	joined = ft_strjoin(user_host, " " COLOR_PATH);
	free(user_host);
	if (!joined)
		return (free(prompt_path), NULL);
	tmp = ft_strjoin(joined, prompt_path);
	free(joined);
	free(prompt_path);
	if (!tmp)
		return (NULL);
	joined = ft_strjoin(tmp, COLOR_RESET PROMPT);
	free(tmp);
	return (joined);
}

char	*ft_build_prompt(void)
{
	char	hostname[HOST_NAME_MAX + 1];
	char	cwd[PATH_MAX + 1];
	char	*user_host;
	char	*user;

	user = getenv("USER");
	if (!user)
		user = "user";
	if (gethostname(hostname, sizeof(hostname)) != 0)
		ft_strlcpy(hostname, "minishell", sizeof(hostname));
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "?", sizeof(cwd));
	user_host = ft_prompt_userhost(user, hostname);
	if (!user_host)
		return (NULL);
	return (ft_prompt_path(user_host, cwd));
}
