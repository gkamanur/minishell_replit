/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:21:12 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/11 14:55:46 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char	*ft_expand_braced_var(const char *input, size_t *idx_ptr,
// 		t_shell *shell)
// {
// 	size_t	start;
// 	char	*var_name;
// 	char	*string;

// 	(*idx_ptr)++;
// 	start = *idx_ptr;
// 	while (input[*idx_ptr] && input[*idx_ptr] != '}')
// 		(*idx_ptr)++;
// 	if (input[*idx_ptr] != '}')
// 		return (ft_strdup("${"));
// 	var_name = ft_substr(input, start, *idx_ptr - start);
// 	if (!var_name)
// 		return (NULL);
// 	string = ft_dup_env_value(var_name, shell);
// 	if (!string)
// 		string = ft_strdup("");
// 	free(var_name);
// 	(*idx_ptr)++;
// 	return (string);
// }

// static char	*expand_last_status(size_t *idx_ptr, t_shell *shell)
// {
// 	(*idx_ptr)++;
// 	return (ft_get_lastcmd_string(shell->last_status));
// }

// char	*ft_process_dollar(const char *input, size_t *idx_ptr, t_shell *shell)
// {
// 	size_t	start;
// 	char	*string;
// 	char	*var_name;

// 	if (input[*idx_ptr] == '?')
// 		return (expand_last_status(idx_ptr, shell));
//     if (input[*idx_ptr]  == '$') // special case: PID
//     {
//         (*idx_ptr)++;
//         return ft_itoa(getpid());
//     }
// 	if (input[*idx_ptr] == '{')
// 		return (ft_expand_braced_var(input, idx_ptr, shell));
// 	if (is_valid_var_char(input[*idx_ptr], 1))
// 	{
// 		start = *idx_ptr;
// 		while (input[*idx_ptr] && is_valid_var_char(input[*idx_ptr], 0))
// 			(*idx_ptr)++;
// 		var_name = ft_substr(input, start, *idx_ptr - start);
// 		if (!var_name)
// 			return (NULL);
// 		string = ft_dup_env_value(var_name, shell);
// 		if (!string)
// 			string = ft_strdup("");
// 		free(var_name);
// 		return (string);
// 	}
// 	// When $ is not followed by valid variable char, treat as literal $
// 	return (ft_strdup("$"));
// }
char *ft_getenv(t_shell *shell, const char *varname)
{
    t_env_var *env;

    if (!shell || !varname)
        return NULL;

    env = shell->env_list;
    while (env)
    {
        if (ft_strcmp(env->envar_name, varname) == 0)
            return env->envar_value; // return pointer to value
        env = env->next_envar;
    }
    return NULL; // not found
}

char *ft_process_dollar(const char *str, size_t *i, t_shell *shell)
{
    char varname[256];
    size_t j = 0;
    char *value;

    if (str[*i] == '?') // special case: last status code
    {
        (*i)++;
        return ft_itoa(shell->last_status);
    }
    if (str[*i] == '$') // special case: PID
    {
        (*i)++;
        return ft_itoa(getpid());
    }
    if (str[*i] == '{') // ${VAR} syntax
    {
        (*i)++; // skip '{'
        while (str[*i] && str[*i] != '}' && j < sizeof(varname) - 1)
            varname[j++] = str[(*i)++];
        if (str[*i] == '}')
            (*i)++; // skip '}'
        varname[j] = '\0';
    }
    else
    {
        // Normal variable name [A-Za-z_][A-Za-z0-9_]*
        if (!ft_isalpha(str[*i]) && str[*i] != '_')
            return ft_strdup("$"); // "$x" invalid start → keep '$'
        while ((ft_isalnum(str[*i]) || str[*i] == '_') && j < sizeof(varname) - 1)
            varname[j++] = str[(*i)++];
        varname[j] = '\0';
    }

    // Lookup variable in env
    value = ft_getenv(shell, varname);
    if (!value)
        return ft_strdup(""); // undefined → empty
    return ft_strdup(value);
}

char *ft_expand_tilde(const char *str, size_t *i, t_shell *shell)
{
    char *home;
    
    (void)shell;
    if (str[*i] == '~')
    {
        (*i)++;
        home = getenv("HOME");
        if (home)
            return ft_strdup(home);
        else
            return ft_strdup("~");
    }
    return ft_strdup("~");
}

char *ft_create_expansion_main(const char *input, t_token *token, t_shell *shell)
{
    size_t i;
    char *expand_string;
    char *piece;

	(void)input; // input is unused now, but kept for compatibility
    // SINGLE-quoted: return literal content without outer quotes
    if (token && token->quote == SINGLE)
        return ft_strdup(token->token_value);

    // DOUBLE-quoted or unquoted: expand $ and ~
    expand_string = ft_strdup("");
    if (!expand_string)
        return NULL;

    i = 0;
    // Handle tilde expansion at the beginning
    if (token->token_value[0] == '~' && (token->token_value[1] == '\0' || token->token_value[1] == '/'))
    {
        piece = ft_expand_tilde(token->token_value, &i, shell);
        if (!piece || !ft_append_piece(&expand_string, piece))
            return NULL;
    }
    
    while (token->token_value[i])
    {
        if (token->token_value[i] == '$')
        {
            i++;
            piece = ft_process_dollar(token->token_value, &i, shell);
            if (!piece || !ft_append_piece(&expand_string, piece))
                return NULL;
        }
        else if (token->token_value[i] == '\\' && token->token_value[i + 1])
        {
            i++; // skip backslash
            if (token->quote == DOUBLE)
            {
                // Handle escape sequences in double quotes
                if (token->token_value[i] == '$' || token->token_value[i] == '"' || 
                    token->token_value[i] == '\\' || token->token_value[i] == '\n')
                {
                    piece = ft_char_to_str(token->token_value[i]);
                }
                else
                {
                    // Keep both backslash and character for other escapes
                    char temp[3] = {'\\', token->token_value[i], '\0'};
                    piece = ft_strdup(temp);
                }
            }
            else
            {
                // In unquoted context, backslash escapes the next character
                piece = ft_char_to_str(token->token_value[i]);
            }
            if (!piece || !ft_append_piece(&expand_string, piece))
                return NULL;
            i++;
        }
        else
        {
            piece = ft_char_to_str(token->token_value[i]);
            if (!piece || !ft_append_piece(&expand_string, piece))
                return NULL;
            i++;
        }
		//i++;
    }

    return expand_string;
}







// char	*ft_create_expansion_main(const char *input, t_shell *shell)
// {
//     size_t	i;
//     char	*expand_string;
//     char	*piece;
//     int		in_single;
//     int		in_double;

//     /* If the whole token was single-quoted, everything is literal:
//      * lexer/parser should have set shell->cmd_list->quote for this arg.
//      * In that case return a strdup of the input (no expansion). */

//     in_single = 0;
//     in_double = 0;
//     if (shell && shell->cmd_list && shell->cmd_list->quote == DOUBLE)
//         in_double = 1;
//     if (shell && shell->cmd_list && shell->cmd_list->quote == SINGLE)
//     {
//         return (ft_strdup(input));
//         in_single = 1;
//     }

//     expand_string = ft_strdup("");
//     if (!expand_string)
//         return (NULL);
//     i = 0;
//     while (input[i])
//     {
//         if (input[i] == '\'')
//         {
//             if (!in_double)
//                 in_single = !in_single;
//             else
//             {
//                 if (!ft_append_char_to_expand(&expand_string, '\''))
//                     return (NULL);
//             }
//             i++;
//         }
//         else if (input[i] == '"')
//         {
//             if (!in_single)
//                 in_double = !in_double;
//             else
//             {
//                 if (!ft_append_char_to_expand(&expand_string, '"'))
//                     return (NULL);
//             }
//             i++;
//         }
//         else if (input[i] == '$' && !in_single)
//         {
//             i++;
//             piece = ft_process_dollar(input, &i, shell);
//             if (!ft_append_piece(&expand_string, piece))
//                 return (NULL);
//         }
//         else
//         {
//             piece = ft_char_to_str(input[i++]);
//             if (!ft_append_piece(&expand_string, piece))
//                 return (NULL);
//         }
//     }
//     return (expand_string);
// }
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
	t_token *tok;
    t_comnd *saved_shell_cmds;
    int i;

    /* preserve original shell->cmd_list pointer and restore later */
    saved_shell_cmds = shell->cmd_list;

    while (cmds)
    {
        shell->cmd_list = cmds; // if needed by ft_process_dollar, etc.
        tok = cmds->av_cmd_lst;
        i = 0;

        while (tok && cmds->av_cmd[i])
        {
            expanded = ft_create_expansion_main(cmds->av_cmd[i], tok, shell);

            if (expanded)
            {
                free(cmds->av_cmd[i]);
                cmds->av_cmd[i] = expanded;
            }

            i++;
            tok = tok->next_token;
        }

        remove_empty_arguments(cmds->av_cmd); // optional cleanup
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
