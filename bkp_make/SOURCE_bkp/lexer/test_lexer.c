/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:04:41 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/02 17:13:51 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

const char	*token_type_to_str(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == TOKEN_HEREDOC)
		return ("HEREDOC");
	else if (type == TOKEN_APPEND)
		return ("APPEND");
	else if (type == TOKEN_EOF)
		return ("EOF");
	return ("UNKNOWN");
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->token_value)
			printf("Token %2d: %-12s | Value: '%s' | Quote : %i\n", i,
				token_type_to_str(tokens->type), tokens->token_value,
				tokens->quote);
		else
			printf("Token %2d: %-12s | Value: '%s'\n", i,
				token_type_to_str(tokens->type), "(null)");
		tokens = tokens->next_token;
		i++;
	}
}

char	*add_quotes(const char *s, int i)
{
	char	*res;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	// 2 extra for the quotes + 1 for '\0'
	res = malloc(len + 3);
	if (!res)
		return (NULL);
	if (i == 1)
	{
		res[0] = '\'';
		ft_memcpy(res + 1, s, len);
		res[len + 1] = '\'';
	}
	else if (i == 2)
	{
		res[0] = '"';
		ft_memcpy(res + 1, s, len);
		res[len + 1] = '"';
	}
	res[len + 2] = '\0';
	return (res);
}

void	quotes_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->quote == 1)
			tokens->token_value = add_quotes(tokens->token_value, 1);
		else if (tokens->quote == 2)
			tokens->token_value = add_quotes(tokens->token_value, 2);
		tokens = tokens->next_token;
		i++;
	}
}

void	print_array(char **av)
{
	int	i;

	if (!av)
		return ;
	i = 0;
	while (av[i])
	{
		printf("%s\t", av[i]);
		i++;
	}
}

// Helper: Convert token type enum to string for easy reading
// const char *token_type_to_str(t_token_type type)
// {
//     switch (type) {
//         case TOKEN_WORD:        return ("WORD");
//         case TOKEN_PIPE:        return ("PIPE");
//         case TOKEN_REDIRECT_IN: return ("REDIRECT_IN");
//         case TOKEN_REDIRECT_OUT:return ("REDIRECT_OUT");
//         case TOKEN_HEREDOC:     return ("HEREDOC");
//         case TOKEN_APPEND:      return ("APPEND");
//         case TOKEN_EOF:         return ("EOF");
//         default:                return ("UNKNOWN");
//     }
// }