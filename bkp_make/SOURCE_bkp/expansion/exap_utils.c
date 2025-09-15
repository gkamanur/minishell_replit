/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 13:58:49 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/28 10:33:40 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_var_char(char c, int start)
{
	if (start)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

char	*ft_dup_env_value(char *var_name, t_shell *shell)
{
	char	*ptr_env_list;
	char	*ptr_array_value;

	// First check regular environment variables
	ptr_env_list = get_env_value(var_name, shell->env_list);
	if (ptr_env_list)
		return (ft_strdup(ptr_env_list));
	
	// Then check array variables (return first element)
	ptr_array_value = ft_get_array_first_element(var_name, shell->array_list);
	if (ptr_array_value)
		return (ft_strdup(ptr_array_value));
	
	return (ft_strdup(""));
}

char	*ft_get_lastcmd_string(int status)
{
	return (ft_itoa(status));
}

int	ft_append_piece(char **expand_string, char *piece)
{
	char	*tmp;

	if (!piece)
	{
		free(*expand_string);
		return (0);
	}
	tmp = ft_strjoin(*expand_string, piece);
	free(*expand_string);
	free(piece);
	*expand_string = tmp;
	if (!*expand_string)
		return (0);
	return (1);
}

char	*ft_char_to_str(char x)
{
	char	buf[2];

	buf[0] = x;
	buf[1] = '\0';
	return (ft_strdup(buf));
}

int	ft_append_char_to_expand(char **expand_string, char c)
{
    char	*tmp;

    tmp = ft_char_to_str(c);
    if (!tmp)
        return (0);
    return (ft_append_piece(expand_string, tmp));
}
