/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:52:54 by robello-          #+#    #+#             */
/*   Updated: 2025/02/15 20:16:18 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ptr_dest;
	const char	*src_ptr;
	size_t		c;

	ptr_dest = dest;
	src_ptr = src;
	c = 0;
	if (!dest && !src)
		return (0);
	if (n == 0)
		return (dest);
	if (dest > src)
		while (n-- > 0)
			((unsigned char *)ptr_dest)[n] = ((unsigned char *)src_ptr)[n];
	else
	{
		while (c < n)
		{
			ptr_dest[c] = src_ptr[c];
			c++;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char	src[] = "Copying some bytes into destination string.";
// 	char	dest[5];
// 	char	src0[] = "Copying some BYTES into destination string.";
// 	char	dest0[15];
// 	size_t	n;

// 	n = 20;
// 	ft_memmove(dest, src, n);
// 	printf("SOURCE: \"%s\"\n", src);
// 	printf("\"%s\"\n\n", dest);
// 	n = 35;
// 	ft_memmove(dest0, src0, n);
// 	printf("SOURCE: \"%s\"\n", src0);
// 	printf("\"%s\"\n", dest0);
// 	return (0);
// }
