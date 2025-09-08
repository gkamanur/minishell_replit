/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:02:11 by gkamanur          #+#    #+#             */
/*   Updated: 2025/09/02 15:39:10 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_pipe(char x)
{
	if (x == '|')
		return (1);
	return (0);
}

int	ft_is_metacharacter(char x)
{
	if (ft_is_redirect_char(x) || ft_is_pipe(x) || x == '(' || x == ')')
		return (1);
	return (0);
}

int	ft_is_word_char(char x)
{
	if (x && !ft_is_space(x) && !ft_is_metacharacter(x) && !ft_is_quote(x))
		return (1);
	return (0);
}

