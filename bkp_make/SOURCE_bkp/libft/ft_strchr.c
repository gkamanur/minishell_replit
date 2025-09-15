/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:16:41 by robello-          #+#    #+#             */
/*   Updated: 2024/11/28 15:02:03 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = c % 256;
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

// int	main(void)
// {
// 	char	s[] = "Looking for character X within the string";
// 	char	empty[] = "";
// 	char	*found;
// 	int		c;

// 	c = 'X';
// 	found = ft_strchr(s, c);
// 	if (found == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, found - s);
// 	c = 1024;
// 	found = ft_strchr(s, c);
// 	if (found == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, found - s);
// 	c = 'l';
// 	found = ft_strchr(s, c);
// 	if (found == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, found - s);
// 	c = '\0';
// 	found = ft_strchr(empty, c);
// 	if (found == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("Null Terminator %c found at index %ld\n", c, found - empty);
// 	c = '\0';
// 	found = ft_strchr(s, c);
// 	if (found == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("Null Terminator %c found at index %ld\n", c, found - s);
// 	return (0);
// }
