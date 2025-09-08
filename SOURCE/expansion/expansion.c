/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:21:12 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/01 12:54:32 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_expand_braced_var(const char *input, size_t *idx_ptr,
		t_shell *shell)
{
	size_t	start;
	char	*var_name;
	char	*string;

	(*idx_ptr)++;
	start = *idx_ptr;
	while (input[*idx_ptr] && input[*idx_ptr] != '}')
		(*idx_ptr)++;
	if (input[*idx_ptr] != '}')
		return (ft_strdup("${"));
	var_name = ft_substr(input, start, *idx_ptr - start);
	if (!var_name)
		return (NULL);
	string = ft_dup_env_value(var_name, shell);
	if (!string)
		string = ft_strdup("");
	free(var_name);
	(*idx_ptr)++;
	return (string);
}

static char	*expand_last_status(size_t *idx_ptr, t_shell *shell)
{
	(*idx_ptr)++;
	return (ft_get_lastcmd_string(shell->last_status));
}

char	*ft_process_dollar(const char *input, size_t *idx_ptr, t_shell *shell)
{
	size_t	start;
	char	*string;
	char	*var_name;

	if (input[*idx_ptr] == '?')
		return (expand_last_status(idx_ptr, shell));
	if (input[*idx_ptr] == '{')
		return (ft_expand_braced_var(input, idx_ptr, shell));
	if (is_valid_var_char(input[*idx_ptr], 1))
	{
		start = *idx_ptr;
		while (input[*idx_ptr] && is_valid_var_char(input[*idx_ptr], 0))
			(*idx_ptr)++;
		var_name = ft_substr(input, start, *idx_ptr - start);
		if (!var_name)
			return (NULL);
		string = ft_dup_env_value(var_name, shell);
		if (!string)
			string = ft_strdup("");
		free(var_name);
		return (string);
	}
	// When $ is not followed by valid variable char, treat as literal $
	return (ft_strdup("$"));
}

char	*ft_create_expansion_main(const char *input, t_shell *shell)
{
    size_t	i;
    char	*expand_string;
    char	*piece;
    int		in_single;
    int		in_double;

    /* If the whole token was single-quoted, everything is literal:
     * lexer/parser should have set shell->cmd_list->quote for this arg.
     * In that case return a strdup of the input (no expansion). */
    if (shell && shell->cmd_list && shell->cmd_list->quote == SINGLE)
        return (ft_strdup(input));
    in_single = 0;
    in_double = 0;
    if (shell && shell->cmd_list && shell->cmd_list->quote == DOUBLE)
        in_double = 1;

    expand_string = ft_strdup("");
    if (!expand_string)
        return (NULL);
    i = 0;
    while (input[i])
    {
        if (input[i] == '\'')
        {
            if (!in_double)
                in_single = !in_single;
            else
            {
                if (!ft_append_char_to_expand(&expand_string, '\''))
                    return (NULL);
            }
            i++;
        }
        else if (input[i] == '"')
        {
            if (!in_single)
                in_double = !in_double;
            else
            {
                if (!ft_append_char_to_expand(&expand_string, '"'))
                    return (NULL);
            }
            i++;
        }
        else if (input[i] == '$' && !in_single)
        {
            i++;
            piece = ft_process_dollar(input, &i, shell);
            if (!ft_append_piece(&expand_string, piece))
                return (NULL);
        }
        else
        {
            piece = ft_char_to_str(input[i++]);
            if (!ft_append_piece(&expand_string, piece))
                return (NULL);
        }
    }
    return (expand_string);
}
// ...existing code...
// ...existing code...
// ...existing code...

// ...existing code...
static void	remove_empty_arguments(char **av_cmd)
{
    int i, j;
    
    if (!av_cmd)
        return;
        
    i = 0;
    while (av_cmd[i])
    {
        if (ft_strlen(av_cmd[i]) == 0)
        {
            // Remove this empty argument
            free(av_cmd[i]);
            j = i;
            while (av_cmd[j + 1])
            {
                av_cmd[j] = av_cmd[j + 1];
                j++;
            }
            av_cmd[j] = NULL;
            // Don't increment i since we're now at a new argument
            continue;
        }
        i++;
    }
}

void	ft_expand_cmds(t_comnd *cmds, t_shell *shell)
{
    char	*expanded;
    int		i;
    t_comnd *saved_shell_cmds;

    /* preserve original shell->cmd_list pointer and restore later */
    saved_shell_cmds = shell->cmd_list;
    while (cmds)
    {
        /* let expansion see the quote info for the current argument */
        shell->cmd_list = cmds;
        i = 0;
        while (cmds->av_cmd && cmds->av_cmd[i])
        {
            expanded = ft_create_expansion_main(cmds->av_cmd[i], shell);
            if (expanded)
            {
                free(cmds->av_cmd[i]);
                cmds->av_cmd[i] = expanded;
            }
            i++;
        }
        remove_empty_arguments(cmds->av_cmd);
        cmds = cmds->next;
    }
    /* restore original pointer */
    shell->cmd_list = saved_shell_cmds;
}

// void	ft_expand_cmds(t_comnd *cmds, t_shell *shell)
// {
// 	char	*expanded;
// 	int		i;

// 	while (cmds)
// 	{
// 		i = 0;
// 		while (cmds->av_cmd && cmds->av_cmd[i])
// 		{
// 			expanded = ft_create_expansion_main(cmds->av_cmd[i], shell);
// 			if (expanded)
// 			{
// 				free(cmds->av_cmd[i]);
// 				cmds->av_cmd[i] = expanded;
// 			}
// 			i++;
// 		}
// 		cmds = cmds->next;
// 	}
// }
