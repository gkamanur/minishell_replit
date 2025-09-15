/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:03:13 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/15 17:06:14 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*lex_double_redirect(const char *input_line, int *input_ptr)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	*input_ptr += 2;
	if (input_line[*input_ptr - 2] == '<' && input_line[*input_ptr - 1] == '<')
		type = TOKEN_HEREDOC;
	else
		type = TOKEN_APPEND;
	if (type == TOKEN_HEREDOC)
		value = ft_strdup("<<");
	else
		value = ft_strdup(">>");
	if (!value)
		return (NULL);
	token = ft_new_token(type, value, 0);
	if (!token)
		free(value);
	return (token);
}

t_token	*lex_redirect(const char *input_line, int *input_ptr)
{
	t_token_type	type;
	t_token			*token;
	char			*value;

	if (input_line[*input_ptr] == '<')
	{
		type = TOKEN_REDIRECT_IN;
	}
	else
	{
		type = TOKEN_REDIRECT_OUT;
	}
	value = ft_substr(input_line, *input_ptr, 1);
	if (!value)
		return (NULL);
	(*input_ptr)++;
	token = ft_new_token(type, value, 0);
	if (!token)
		free(value);
	return (token);
}

t_token	*lex_single_quote(const char *input_line, int *input_ptr)
{
	int		start;
	int		len;
	char	*value;
	t_token	*token = NULL;

	start = *input_ptr + 1;
	(*input_ptr)++;
	while (input_line[*input_ptr] && input_line[*input_ptr] != '\'')
		(*input_ptr)++;
	if (!input_line[*input_ptr])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	len = *input_ptr - start;
	value = ft_substr(input_line, start, len);
	if (!value)
		return (NULL);
	token = ft_new_token(TOKEN_WORD, value, SINGLE);
	if (!token)
		free(value);
	(*input_ptr)++;
	return (token);
}

t_token	*lex_double_quote(const char *input_line, int *input_ptr)
{
	int		start;
	int		len;
	char	*value;
	t_token	*token = NULL;

	start = *input_ptr + 1;
	(*input_ptr)++;
	while (input_line[*input_ptr] && input_line[*input_ptr] != '"')
	{
		// Handle escape sequences in double quotes
		if (input_line[*input_ptr] == '\\' && input_line[*input_ptr + 1])
		{
			// Skip the escape character and the next character
			(*input_ptr) += 2;
		}
		else
			(*input_ptr)++;
	}
	if (!input_line[*input_ptr])
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	len = *input_ptr - start;
	value = ft_substr(input_line, start, len);
	if (!value)
		return (NULL);
	token = ft_new_token(TOKEN_WORD, value, DOUBLE);
	
	if (!token)
		free(value);
	(*input_ptr)++;
	return (token);
}

t_token	*lex_metacharacter(const char *input_line, int *input_ptr)
{
	t_token	*token;
	char	chara[2];

	if (input_line[*input_ptr + 1] && ((input_line[*input_ptr]
				== '<' && input_line[*input_ptr + 1] == '<')
			|| (input_line[*input_ptr]
				== '>' && input_line[*input_ptr + 1] == '>')))
		return (lex_double_redirect(input_line, input_ptr));
	if (ft_is_redirect_char(input_line[*input_ptr]))
		return (lex_redirect(input_line, input_ptr));
	if (ft_is_pipe(input_line[*input_ptr]))
	{
		chara[0] = input_line[*input_ptr];
		chara[1] = '\0';
		(*input_ptr)++;
		token = ft_new_token(TOKEN_PIPE, ft_strdup(chara), 0);
		if (!token)
			return (NULL);
		return (token);
	}
	if (input_line[*input_ptr] == '(' || input_line[*input_ptr] == ')')
	{
		chara[0] = input_line[*input_ptr];
		chara[1] = '\0';
		(*input_ptr)++;
		token = ft_new_token(TOKEN_WORD, ft_strdup(chara), 0);
		if (!token)
			return (NULL);
		return (token);
	}
	return (NULL);
}
