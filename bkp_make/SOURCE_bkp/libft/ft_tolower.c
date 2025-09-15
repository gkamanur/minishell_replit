/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:27:41 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 15:00:48 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

// int	main(void)
// {
// 	int	letter;
// 	int	letter1;
// 	int	letter2;

// 	letter = 70;
// 	letter1 = 100;
// 	letter2 = 50;
// 	printf("%c	", letter);
// 	letter = ft_tolower(letter);
// 	printf("%c\n", letter);
// 	printf("%c	", letter1);
// 	letter1 = ft_tolower(letter1);
// 	printf("%c\n", letter1);
// 	printf("%c	", letter2);
// 	letter1 = ft_tolower(letter2);
// 	printf("%c", letter2);
// 	return (0);
// }
