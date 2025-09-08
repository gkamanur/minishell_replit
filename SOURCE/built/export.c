/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:26:40 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/28 15:53:23 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char *strip_single_paren(const char *s)
{
	size_t len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	// optional surrounding spaces are already handled elsewhere; keep it simple here
	if (len >= 2 && s[0] == '(' && s[len - 1] == ')')
		return (ft_substr(s, 1, len - 2));
	return (ft_strdup(s));
}

static void	init_export_state(t_export_state *state)
{
	state->last_name = NULL;
	state->last_was_assignment = 0;
	state->status = 0;
}

static void	handle_invalid_arg(char *arg, t_export_state *state,
		t_env_var **env_list)
{
	char	*old_val;
	char	*tmp;
	char	*joined;

	if (state->last_was_assignment && state->last_name && !ft_strchr(arg, '='))
	{
		old_val = get_env_value(state->last_name, *env_list);
		tmp = ft_strjoin(old_val ? old_val : "", " ");
		joined = ft_strjoin(tmp, arg);
		free(tmp);
		ft_set_env_var(state->last_name, joined, env_list);
		free(joined);
	}
	else
	{
		print_export_error(arg);
		state->status = 1;
		g_gb.last_sig = 1;
	}
	if (state->last_name)
	{
		free(state->last_name);
		state->last_name = NULL;
	}
	state->last_was_assignment = 0;
}

static void	process_assignment(char *arg, char *equals, t_export_state *state,
		t_env_var **env_list)
{
	char	*name;
	char	*value;

	name = ft_substr(arg, 0, equals - arg);
	{
		char *raw = ft_strdup(equals + 1);
		char *normalized = strip_single_paren(raw);
		free(raw);
		value = normalized;
	}
	ft_set_env_var(name, value, env_list);
	if (state->last_name)
		free(state->last_name);
	state->last_name = ft_strdup(name);
	state->last_was_assignment = 1;
	free(name);
	free(value);
}

static void	process_non_assignment(char *arg, t_export_state *state,
		t_env_var **env_list)
{
	if (!get_env_value(arg, *env_list))
		ft_set_env_var(arg, "", env_list);
	if (state->last_name)
	{
		free(state->last_name);
		state->last_name = NULL;
	}
	state->last_was_assignment = 0;
}


int	builtin_export(char **av_cmd, t_env_var **env_list, char *arg, char *equals)
{
	t_export_state	state;
	int				i;

	i = 1;
	init_export_state(&state);
	if (!av_cmd[1])
	{
		print_export_list(*env_list);
		return (0);
	}
	while (av_cmd && av_cmd[i])
	{
		arg = av_cmd[i];
		equals = ft_strchr(arg, '=');
		if (!is_valid_export_arg(arg))
			handle_invalid_arg(arg, &state, env_list);
		else if (equals)
			process_assignment(arg, equals, &state, env_list);
		else
			process_non_assignment(arg, &state, env_list);
		i++;
	}
	if (state.last_name)
		free(state.last_name);
	return (state.status);
}
