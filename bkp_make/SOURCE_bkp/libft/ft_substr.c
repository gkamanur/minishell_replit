/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:50:12 by robello-          #+#    #+#             */
/*   Updated: 2024/11/26 15:54:06 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subst;
	size_t	i;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	if (start >= size)
		return (ft_strdup(""));
	size = size - start;
	if (size > len)
		size = len;
	subst = (char *)malloc(size + 1);
	if (subst == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		subst[i] = s[start + i];
		i++;
	}
	subst[i] = '\0';
	return (subst);
}

// int	main(void)
// {
// 	char			string[] = "Getting a subtring from this string.";
// 	char			*subst;
// 	unsigned int	start;
// 	size_t			len;

// 	start = 10;
// 	len = 18;
// 	subst = ft_substr(string, start, len);
// 	printf("Original:	\"%s\"\n", string);
// 	printf("substring:	\"%s\"\n", subst);
// 	//printf("starting at index: %u", start);
// free(subst);
// 	start = 40;
// 	len = 18;
// 	subst = ft_substr(string, start, len);
// 	printf("\n\n");
// 	printf("Original:	\"%s\"\n", string);
// 	printf("substring:	\"%s\"\n", subst);
// 	//printf("starting at index: %u", start);
// free(subst);
// 	return (0);
// }
