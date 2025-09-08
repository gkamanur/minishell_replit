/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:09:48 by robello-          #+#    #+#             */
/*   Updated: 2025/03/30 17:39:51 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	a;
	size_t	b;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	join = ((char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (join == NULL)
		return (NULL);
	a = 0;
	b = 0;
	while (s1[a])
	{
		join[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		join[a + b] = s2[b];
		b++;
	}
	join[a + b] = '\0';
	return (join);
}

// int	main(void)
// {
// 	char	s1[] = "Creating a new string ";
// 	char	s2[] = "out of two strings, s1 and s2, looking nice!";
// 	char	*join;

// 	printf("\"%s\"\n\"%s\"\n", s1, s2);
// 	join = ft_strjoin(s1, s2);
// 	printf("\n\"%s\"", join);
// 	free(join);
// 	return (0);
// }
