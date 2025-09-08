/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:25:08 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:56:54 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		*ptr = '\0';
		ptr++;
	}
}

// int	main(void)
// {
// 	char	str[] = "Zeroing n bytes of this string just for fun.";
// 	char	str0[] = "Zeroing n bytes of this string just because.";
// 	char	str1[] = "Zeroing n bytes of this string just for fun.";
// 	char	str2[] = "Zeroing n bytes of this string just because.";
// 	size_t	n;

// 	n = 11;
// 	printf("%s\n", str);
// 	ft_bzero(str, n);
// 	printf("After zeroing:  %s\n", str);
// 	n = 5;
// 	printf("%s\n", str0);
// 	ft_bzero(str0 + 15, n);
// 	printf("After zeroing:  %s\n\n", str0);
// 	n = 11;
// 	printf("%s\n", str1);
// 	bzero(str1, n);
// 	printf("After zeroing:  %s\n", str1);
// 	n = 5;
// 	printf("%s\n", str2);
// 	bzero(str2 + 15, n);
// 	printf("After zeroing: %s\n", str2);
// 	return (0);
// }
