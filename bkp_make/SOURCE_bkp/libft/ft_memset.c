/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:53:35 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:57:26 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	pastebyte;

	ptr = (unsigned char *)s;
	pastebyte = (unsigned char)c;
	while (n--)
	{
		*ptr = pastebyte;
		ptr++;
	}
	return (s);
}

// int	main(void)
// {
// 	char	str[] = "Filling with n bytes a block of memory pointed to by s";
// 	char	str0[] = "Filling 123467891011 a block of memory pointed to by s";
// 	//int		str1[] = {1, 2, 3, 4, 5, 6, 7, 11, 12, 897, 45, 456, 45};
// 	//int		len;
// 	int		c;
// 	int		a;
// 	size_t	n;

// 	c = 1;
// 	n = 7;
// 	a = 0;
// 	//len = sizeof(str1) / sizeof(str1[0]);
// 	ft_putstr(str);
// 	ft_putchar('\n');
// 	ft_memset(str, c, n);
// 	ft_putstr(str);
// 	ft_putchar('\n');
// 	ft_putchar('\n');
// 	ft_putstr(str0);
// 	ft_putchar('\n');
// 	ft_memset(str0 + 20, c, n);
// 	ft_putstr(str0);
// 	ft_putchar('\n');
// 	ft_putchar('\n');
// 	// while (a < len)
// 	// {
// 	// 	ft_putnbr(str1[a]);
// 	// 	ft_putchar(' ');
// 	// 	a++;
// 	// }
// 	// ft_putchar('\n');
// 	// ft_memset(str1 + 3, c, n);
// 	// a = 0;
// 	// while (a < len)
// 	// {
// 	// 	ft_putnbr(str1[a]);
// 	// 	ft_putchar(' ');
// 	// 	a++;
// 	// }
// 	return (0);
// }
