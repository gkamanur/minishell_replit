/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:10:46 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/28 10:28:04 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*append_piece(char *result, char *piece)
{
	char	*tmp;

	if (!piece)
	{
		free(result);
		return (NULL);
	}
	tmp = ft_strjoin(result, piece);
	free(result);
	free(piece);
	return (tmp);
}

static char	*extract_normal_text(const char *content, size_t *i)
{
	size_t	start;

	start = *i;
	while (content[*i] && content[*i] != '$')
		(*i)++;
	return (ft_substr(content, start, *i - start));
}

static char	*extract_piece(const char *content, size_t *i, t_shell *shell)
{
	if (content[*i] == '$')
	{
		(*i)++;
		return (ft_process_dollar(content, i, shell));
	}
	else
		return (extract_normal_text(content, i));
}

char	*ft_expand_string(const char *content, t_shell *shell)
{
	size_t	i;
	char	*result;
	char	*piece;

	if (!content)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (content[i])
	{
		piece = extract_piece(content, &i, shell);
		result = append_piece(result, piece);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*ft_process_quote(const char *input, size_t *idx_ptr, t_shell *shell)
{
	char	quote;
	size_t	start;
	char	*content;
	char	*expanded;

	quote = input[*idx_ptr];
	(*idx_ptr)++;
	start = *idx_ptr;
	while (input[*idx_ptr] && input[*idx_ptr] != quote)
		(*idx_ptr)++;
	content = ft_substr(input, start, *idx_ptr - start);
	if (!content)
		return (NULL);
	if (input[*idx_ptr] == quote)
		(*idx_ptr)++;
	if (quote == '"')
	{
		expanded = ft_expand_string(content, shell);
		free(content);
		return (expanded);
	}
	return (content);
}



