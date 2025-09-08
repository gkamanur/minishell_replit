/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:57:31 by robello-          #+#    #+#             */
/*   Updated: 2024/11/27 20:09:03 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

// int	main(void)
// {
// 	char	src[] = {"Learning C will eventually make sense"};
// 	char	dest[5];
// 	char	src1[] = "Oooyys s11hf1";
// 	char	dest1[16];
// 	char	src2[] = "changing to blocksF SaF Adds/D";
// 	char	dest2[8];
// 	char	src3[] = "";
// 	char	dest3[10];
// 	char	src4[] = "?_ lowercase 67!";
// 	char	dest4[30];
// 	char	src5[] = "function strlcpy() in action";
// 	char	dest5[3];

// 	printf("%zu ", ft_strlcpy(dest, src, sizeof(dest)));
// 	printf("%s\n", dest);
// 	printf("%zu ", ft_strlcpy(dest1, src1, sizeof(dest1)));
// 	printf("%s\n", dest1);
// 	printf("%zu ", ft_strlcpy(dest2, src2, sizeof(dest2)));
// 	printf("%s\n", dest2);
// 	printf("%zu ", ft_strlcpy(dest3, src3, sizeof(dest3)));
// 	printf("%s\n", dest3);
// 	printf("%zu ", ft_strlcpy(dest4, src4, sizeof(dest4)));
// 	printf("%s\n", dest4);
// 	printf("%zu ", ft_strlcpy(dest5, src5, sizeof(dest5)));
// 	printf("%s\n", dest5);
// 	return (0);
// }
