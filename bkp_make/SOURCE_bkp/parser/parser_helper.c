/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:07:04 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/11 14:10:15 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	handle_redirection_error(t_token *filename_token)
{
	char *str;

	if (!filename_token)
		str = "newline";
	else
		str = filename_token->token_value;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	g_gb.last_status_code = 2;
	return (1);
}


int	process_redirection(t_token *token, t_comnd *cmd)
{
	char			**target;
	t_token			*filename_token;
	t_token_type	redir_type;
	int				fd;

	filename_token = token->next_token;
	if (!filename_token)
    	return (handle_redirection_error(NULL)); //2
	target = NULL;
	redir_type = token->type;
	if (redir_type == TOKEN_HEREDOC)
		target = &cmd->delimiter;
	else if (redir_type == TOKEN_REDIRECT_OUT || redir_type == TOKEN_APPEND)
	{
		target = &cmd->outfile_name;
		// If there's already an outfile name, create that file (like bash does)
		if (*target)
		{
			if (redir_type == TOKEN_REDIRECT_OUT)
				fd = open(*target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else // TOKEN_APPEND
				fd = open(*target, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd >= 0)
				close(fd);
			// Don't return error here - bash continues even if intermediate files fail
		}
	}
	else if (redir_type == TOKEN_REDIRECT_IN)
		target = &cmd->infile_name;
	if (*target)
		free(*target);
	*target = ft_strdup(filename_token->token_value);
	if (!*target)
		return (-1);
	cmd->redirec_type = redir_type;
	return (1);
}

int	parse_redirection(t_token **tok_ptr, t_comnd *cmd)
{
	int ret;
	t_token	*token;

	token = *tok_ptr;
	if (!token || !is_redirection(token->type))
		return (0);
	ret = process_redirection(token, cmd);
	if (ret > 0)
	{
		if (token->next_token)
			*tok_ptr = token->next_token->next_token;
		else
			*tok_ptr = NULL;
	}
	return (ret);
}

t_token *dup_token(const t_token *src)
{
    t_token *new;

    if (!src)
        return NULL;
    new = malloc(sizeof(t_token));
    if (!new)
        return NULL;
    new->type = src->type;
    new->quote = src->quote;
    new->token_value = ft_strdup(src->token_value);
    if (!new->token_value)
    {
        free(new);
        return NULL;
    }
    new->next_token = NULL;
    return new;
}

int	add_argument(t_cmd_args *args, t_token *token)
{
	char	**tmp;
	t_token	**tmp_tokens;
	t_token *newtok;
	 
	if (args->argc + 1 >= args->capacity)
	{
		tmp = realloc(args->argv, sizeof(char *) * args->capacity * 2);
		if (!tmp)
			return (0);
		args->argv = tmp;

		tmp_tokens = realloc(args->arg_tokens, sizeof(t_token *) * args->capacity * 2);
		if (!tmp_tokens)
			return 0;
		args->arg_tokens = tmp_tokens;
		
		args->capacity *= 2;
	}
	args->argv[args->argc] = ft_strdup(token->token_value);
	if (!args->argv[args->argc])
		return (0);
	newtok = dup_token(token);
    if (!newtok)
    {
        free(args->argv[args->argc]);
        return (0);
    }

    args->arg_tokens[args->argc] = newtok;
	args->argc++;
	return (1);
}

int	process_token(t_token **token_ptr, t_comnd *cmd, t_cmd_args *args)
{
	t_token	*token;
	int		res;

	token = *token_ptr;
	if (token->quote == 1)
		cmd->quote = 1;
	else if (token->quote == 2)
		cmd->quote = 2;
	if (token->type == TOKEN_WORD)
	{
		// Allow parentheses for array assignments (VAR=(...)) and quoted strings
		if ((ft_strchr(token->token_value, '(') || ft_strchr(token->token_value, ')'))
			&& !ft_is_array_assignment(token->token_value) && token->quote == NA)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(token->token_value, 2);
			ft_putstr_fd("'\n", 2);
			g_gb.last_status_code = 2;
			return (-1);
		}
		if (!add_argument(args, token))
			return (0);
		*token_ptr = token->next_token;
	}
	else if (is_redirection(token->type))
	{
		res = parse_redirection(token_ptr, cmd);
		if (res <= 0)
			return (res);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		g_gb.last_status_code = 2;
		return (-1);
	}
	return (1);
}