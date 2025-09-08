/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:07:52 by robello           #+#    #+#             */
/*   Updated: 2025/08/28 13:10:42 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_potential_array_assignment(const char *input_line, int start_pos)
{
	int	i = start_pos;
	
	// Look for pattern: IDENTIFIER=( but reject IDENTIFIER=((
	while (input_line[i] && (ft_isalnum(input_line[i]) || input_line[i] == '_'))
		i++;
	if (input_line[i] != '=')
		return (0);
	i++;
	if (input_line[i] != '(')
		return (0);
	// Reject double parentheses - this should be a syntax error
	if (input_line[i + 1] == '(')
		return (0);
	return (1);
}

t_token	*lex_word(const char *input_line, int *input_ptr)
{
	t_token	*token;
	char	*value;
	int		start;
	int		paren_depth = 0;
	int		is_array_assignment;

	start = *input_ptr;
	is_array_assignment = is_potential_array_assignment(input_line, start);
	
	if (is_array_assignment)
	{
		// For array assignments, include parentheses and spaces in the word token
		while (input_line[*input_ptr])
		{
			if (input_line[*input_ptr] == '(')
				paren_depth++;
			else if (input_line[*input_ptr] == ')')
			{
				paren_depth--;
				(*input_ptr)++;
				if (paren_depth == 0)
					break;
				continue;
			}
			// Allow spaces inside parentheses for array assignments
			else if (ft_is_space(input_line[*input_ptr]) && paren_depth == 0)
				break;
			(*input_ptr)++;
		}
	}
	else
	{
		// Normal word parsing
		while (ft_is_word_char(input_line[*input_ptr]))
			(*input_ptr)++;
	}
	
	value = ft_substr(input_line, start, *input_ptr - start);
	if (!value)
		return (NULL);
	token = ft_new_token(TOKEN_WORD, value);
	if (!token)
		free(value);
	return (token);
}

t_token	*get_next_token(const char *input_line, int *input_ptr)
{
	char	x;

	while (ft_is_space(input_line[*input_ptr]))
		(*input_ptr)++;
	if (input_line[*input_ptr] == '\0')
		return (NULL);
	x = input_line[*input_ptr];
	if (ft_is_single_quote(x))
		return (lex_single_quote(input_line, input_ptr));
	if (ft_is_double_quote(x))
		return (lex_double_quote(input_line, input_ptr));
	if (ft_is_metacharacter(x))
		return (lex_metacharacter(input_line, input_ptr));
	return (lex_word(input_line, input_ptr));
}

t_token	*ft_lexer_main(const char *input_line)
{
	int		input_ptr;
	t_token	*first;
	t_token	*last;
	t_token	*token;
	
	input_ptr = 0;
	first = NULL;
	last = NULL;
	
	if (!input_line || !*input_line)
		return (NULL);

	while (input_line[input_ptr])
	{
		token = get_next_token(input_line, &input_ptr);
		if (!token)
		{
			free_tokens(first);
			return (NULL);
		}
		if (!first)
			first = token;
		else
			last->next_token = token;
		last = token;
	}
	return (first);
}
