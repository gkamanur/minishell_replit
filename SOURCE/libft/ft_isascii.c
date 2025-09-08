/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:38:11 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:56:45 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

// int	main(void)
// {
// 	int	a;
// 	int	asc;

// 	asc = ft_isascii('\0');
// 	printf("%d", asc);
// 	asc = ft_isascii('\t');
// 	printf("%d", asc);
// 	asc = ft_isascii('9');
// 	printf("%d", asc);
// 	asc = ft_isascii('=');
// 	printf("%d", asc);
// 	asc = ft_isascii('e');
// 	printf("%d", asc);
// 	asc = ft_isascii('~');
// 	printf("%d", asc);
// 	asc = ft_isascii(0xE9);
// 	printf("%d", asc);
// 	asc = ft_isascii('<F1>');
// 	printf("%d", asc);
// 	asc = ft_isascii('<E7>');
// 	printf("%d", asc);
// 	asc = ft_isascii('<A9>');
// 	printf("%d", asc);
// 	a = 0;
// 	return (0);
// }
