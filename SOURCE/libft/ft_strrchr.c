/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:01 by robello-          #+#    #+#             */
/*   Updated: 2024/11/30 22:24:27 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	s[] = "Looking\0X for chara\0cter X \0within the string";
// 	char	empty[] = "";
// 	char	*find_last;
// 	int		c;

// 	c = 'X';
// 	find_last = ft_strrchr(s, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, find_last - s);
// 	c = 'r';
// 	find_last = ft_strrchr(s, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, find_last - s);
// 	c = 'z';
// 	find_last = ft_strrchr(s, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, find_last - s);
// 	c = '\0';
// 	find_last = ft_strrchr(empty, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("Null Terminator %c found at index %ld\n", c, find_last - empty);
// 	c = '\0';
// 	find_last = ft_strrchr(s, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("Null Terminator %c found at index %ld\n", c, find_last - s);
// 	printf("\n\n");
// 	c = 'X';
// 	find_last = strrchr(s, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, find_last - s);
// 	c = 105;
// 	find_last = strrchr(s, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, find_last - s);
// 	c = 'z';
// 	find_last = strrchr(s, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("%c found at index %ld\n", c, find_last - s);
// 	c = '\0';
// 	find_last = strrchr(empty, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("Null Terminator %c found at index %ld\n", c, find_last - empty);
// 	c = '\0';
// 	find_last = strrchr(s, c);
// 	if (find_last == NULL)
// 		printf("%c not found\n", c);
// 	else
// 		printf("Null Terminator %c found at index %ld\n", c, find_last - s);
// 	return (0);
// }
