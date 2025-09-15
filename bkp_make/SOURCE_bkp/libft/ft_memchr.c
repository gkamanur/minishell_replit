/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:26:38 by robello-          #+#    #+#             */
/*   Updated: 2024/11/19 16:26:38 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*search;
	size_t			len;

	search = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	len = 0;
	while (len < n)
	{
		if (search[len] == (unsigned char)c)
			return (&search[len]);
		len++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*find;
// 	char	s[] = "Scanning some bytes in this string";
// 	size_t	n;
// 	int		c;

// 	n = 15;
// 	c = 'b';
// 	find = ft_memchr(s, c, n);
// 	if (find == NULL)
// 		printf("c not found");
// 	else
// 		printf("%c found at index %ld", c, find - s);
// 	return (0);
// }
