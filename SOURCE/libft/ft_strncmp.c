/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:23:37 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:59:30 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	w;

	w = 0;
	while (w < n && s1[w] && s2[w])
	{
		if (s1[w] != s2[w])
			return ((unsigned char)s1[w] - (unsigned char)s2[w]);
		w++;
	}
	if (w < n)
		return ((unsigned char)s1[w] - (unsigned char)s2[w]);
	return (0);
}

// int	main(void)
// {
// 	char	string[] = "I wannA compare the content ";
// 	char	string1[] = "I wanna compare the content ";
// 	char	string2[] = "I wanted to compare 3THE3 content ";
// 	char	string3[] = "I wanted to compare the content ";
// 	char	string4[] = "I wannA to compare the content ";
// 	char	string5[] = "I wannA To ";
// 	char	string6[] = "I wanted to compare the content ";
// 	char	string7[] = "I wanted to compare the content ";
// 	size_t	n;
// 	int		diff;

// 	n = 17;
// 	diff = ft_strncmp(string, string1, n);
// 	printf("%d\n", diff);
// 	diff = ft_strncmp(string2, string3, n);
// 	printf("%d\n", diff);
// 	diff = ft_strncmp(string4, string5, n);
// 	printf("%d\n", diff);
// 	diff = ft_strncmp(string6, string7, n);
// 	printf("%d\n", diff);
// 	return (0);
// }
