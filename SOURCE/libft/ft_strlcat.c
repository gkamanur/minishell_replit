/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:09:45 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:59:08 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	ds_len;
	size_t	sr_len;

	ds_len = 0;
	while (dest[ds_len])
		ds_len++;
	sr_len = 0;
	while (src[sr_len])
		sr_len++;
	i = 0;
	if (size <= ds_len)
		return (size + sr_len);
	while (src[i] && (ds_len + i) < (size - 1))
	{
		dest[ds_len + i] = src[i];
		i++;
	}
	dest[ds_len + i] = '\0';
	return (ds_len + sr_len);
}

//int main(void)
// {
// 	char	src[] = " /has been appended.";
// 	char	dest[23] = "Something";
// 	char	src1[] = "/there is enough memory space";
// 	char	dest1[50] = "what happens when ";
// 	char	src2[] = "";
// 	char	dest2[21] = "nothing appended";
// 	char	src3[] = "/good timing";
// 	char	dest3[12] = "Is it";
// 	char	src4[50] = "/too long?";
// 	char	dest4[50] = "is it ";
// 	char	src5[] = " /short?";
// 	char	dest5[24] = "or perhaps too";
// 	printf("%zu ", ft_strlcat(dest, src, sizeof(dest)));
// 	printf("%s\n", dest);
// 	printf("%zu ", ft_strlcat(dest1, src1, sizeof(dest1)));
// 	printf("%s\n", dest1);
// 	printf("%zu ", ft_strlcat(dest2, src2, sizeof(dest2)));
// 	printf("%s\n", dest2);
// 	printf("%zu ", ft_strlcat(dest3, src3, sizeof(dest3)));
// 	printf("%s\n", dest3);
// 	printf("%zu ", ft_strlcat(dest4, src4, sizeof(dest4)));
// 	printf("%s\n", dest4);
// 	printf("%zu ", ft_strlcat(dest5, src5, sizeof(dest5)));
// 	printf("%s\n", dest5);
// 	return (0);
// }