/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:34:44 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:56:46 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return ((c >= ' ' && c <= '~'));
}

// int	main(void)
// {
// 	int	pnt;

// 	pnt = ft_isprint('\a');
// 	printf("%d", pnt);
// 	pnt = ft_isprint('\b');
// 	printf("%d", pnt);
// 	pnt = ft_isprint('\t');
// 	printf("%d", pnt);
// 	pnt = ft_isprint('\n');
// 	printf("%d", pnt);
// 	pnt = ft_isprint('\v');
// 	printf("%d", pnt);
// 	pnt = ft_isprint('5');
// 	printf("%d", pnt);
// 	pnt = ft_isprint('q');
// 	printf("%d", pnt);
// 	pnt = ft_isprint('~');
// 	printf("%d", pnt);
// 	pnt = ft_isprint('T');
// 	printf("%d", pnt);
// 	pnt = ft_isprint(' ');
// 	printf("%d", pnt);
// 	return (0);
// }
