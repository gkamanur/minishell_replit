/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:20:42 by robello-          #+#    #+#             */
/*   Updated: 2024/11/28 13:44:16 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (big[i + j] == '\0' && little[j] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	*res;
// 	size_t	len;
// 	char	big[] = "Another test for this function";
// 	char	little[] = "";
// 	char	big1[] = "Another test for this. function";
// 	char	little1[] = "this.";
// 	char	big2[] = "Did we get the NULL?";
// 	char	little2[] = "1234567789900";
// 	char	big3[] = "o";
// 	char	little3[] = "";
// 	char	big4[] = "this time it seems to be the same but...";
// 	char	little4[] = "this time it seems to be the same but";
// 	char	big5[] = "Hello people of the world";
// 	char	little5[] = "people";
// 	char	big6[] = "The quick brown fox jumps over the lazy dog";
// 	char	little6[] = "fox jumps";
// 	char	big7[] ="Short";
// 	char	little7[] = "Longer Short Substring";

// 	len = 31;
// 	res = ft_strnstr(big, little, len);
// 	if (res == big)
// 		printf("Little is Empty. Big: \"%s\"\n\n", res);
// 	else if (res != NULL)
// 		printf("Found: \"%s\"\n\n", res);
// 	else
// 		printf("Substring not found.\n\n");
// 	len = 35;
// 	res = ft_strnstr(big1, little1, len);
// 	if (res == big1)
// 		printf("Little is Empty. Big: \"%s\"\n\n", res);
// 	else if (res)
// 		printf("Found: \"%s\"\n\n", res);
// 	else
// 		printf("Substring not found.\n\n");
// 	len = 0;
// 	res = ft_strnstr(big2, little2, len);
// 	if (res == big2)
// 		printf("Little is Empty. Big: \"%s\"\n\n", res);
// 	else if (res)
// 		printf("Found: \"%s\"\n\n", res);
// 	else
// 		printf("Substring not found.\n\n");
// 	len = 100;
// 	res = ft_strnstr(big3, little3, len);
// 	if (res == big3)
// 		printf("Little is Empty. Big: \"%s\"\n\n", res);
// 	else if (res)
// 		printf("Found: \"%s\"\n\n", res);
// 	else
// 		printf("Substring not found.\n\n");
// 	len = 30;
// 	res = ft_strnstr(big4, little4, len);
// 	if (res == big4)
// 		printf("Little is Empty. Big: \"%s\"\n\n", res);
// 	else if (res)
// 		printf("Found: \"%s\"\n\n", res);
// 	else
// 		printf("Substring not found.\n\n");
// 	len = 12;
// 	res = ft_strnstr(big5, little5, len);
// 	if (res == big5)
// 		printf("Little is Empty. Big: \"%s\"\n\n", res);
// 	else if (res)
// 		printf("Found: \"%s\"\n\n", res);
// 	else
// 		printf("Substring not found.\n\n");
// 	len = 25;
// 	res = ft_strnstr(big6, little6, len);
// 	if (res == big6)
// 		printf("Little is Empty. Big: \"%s\"\n\n", res);
// 	else if (res)
// 		printf("Found: \"%s\"\n\n", res);
// 	else
// 		printf("Substring not found.\n\n");
// 	len = 25;
// 	res = ft_strnstr(big7, little7, len);
// 	if (res == big7)
// 		printf("Little is Empty. Big: \"%s\"\n\n", res);
// 	else if (res)
// 		printf("Found: \"%s\"\n\n", res);
// 	else
// 		printf("Substring not found.\n\n");
// 	return (0);
// }
