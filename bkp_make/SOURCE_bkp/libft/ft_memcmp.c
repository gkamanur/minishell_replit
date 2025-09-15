/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:16:35 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:56:51 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	s1[] = "This is Atring number one";
// 	char	s2[] = "This is also another string, but number two";
// 	char	s3[] = "another way to test this function";
// 	char	s4[] = "another way";
// 	char	s5[] = {1, 2, 3, 4, 65, 6,7, 8, 9, 10, 11, 12};
// 	char	s6[] = {1, 2, 3, 4, 5, 67, 8, 9, 11, 11, 12};
// 	int		diff;
// 	size_t	n;

// 	n = 10;
// 	diff = ft_memcmp(s1, s2, n);
// 	printf("%d\t", diff);
// 	diff = memcmp(s1, s2, n);
// 	printf("%d\n", diff);
// 	diff = ft_memcmp(s3, s4, n);
// 	printf("%d\t", diff);
// 	diff = memcmp(s3, s4, n);
// 	printf("%d\n", diff);
// 	diff = ft_memcmp(s5, s6, n);
// 	printf("%d\t", diff);
// 	diff = memcmp(s5, s6, n);
// 	printf("%d\n", diff);
// 	return (0);
// }
