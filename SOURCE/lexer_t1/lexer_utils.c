/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:01:05 by gkamanur          #+#    #+#             */
/*   Updated: 2025/08/25 14:48:30 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_space(char x)
{
	if (x == ' ' || x == '\t')
		return (1);
	return (0);
}

int	ft_is_single_quote(char x)
{
	if (x == '\'')
		return (1);
	return (0);
}

int	ft_is_double_quote(char x)
{
	if (x == '"')
		return (1);
	return (0);
}

int	ft_is_quote(char x)
{
	if (ft_is_single_quote(x) || ft_is_double_quote(x))
		return (1);
	return (0);
}

int	ft_is_redirect_char(char x)
{
	if (x == '<' || x == '>')
		return (1);
	return (0);
}
