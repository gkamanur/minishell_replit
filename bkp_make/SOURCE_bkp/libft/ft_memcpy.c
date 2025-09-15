/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:31:38 by robello-          #+#    #+#             */
/*   Updated: 2024/11/28 11:36:52 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (n == 0)
		return (dest);
	if (!dest && !src)
		return (0);
	d = dest;
	s = src;
	i = 0;
	while (n--)
	{
		((unsigned char *)d)[i] = ((unsigned char *)s)[i];
		d++;
		s++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	src[] = "Copying some bytes into destination string.";
// 	char	dest[10];
// 	char	src0[] = "Copying some bytes into destination string.";
// 	char	dest0[10];
// 	size_t	n;

// 	n = 12;
// 	ft_putstr(src);
// 	ft_putstr(dest);
// 	ft_memcpy(dest, src, n);
// 	ft_putchar('\n');
// 	ft_putstr(dest);
// 	ft_putchar('\n');
// 	ft_putchar('\n');
// 	ft_putchar('\n');
// 	ft_putstr(src0);
// 	ft_putchar('\n');
// 	memcpy(dest0, src0, n);
// 	ft_putstr(dest);
// 	return (0);
// }
