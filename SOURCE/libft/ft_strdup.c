/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:17:11 by robello-          #+#    #+#             */
/*   Updated: 2025/08/06 01:34:50 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		size;
	int		c;
	char	*dup;

	size = 0;
	while (src[size])
		size++;
	dup = (char *)malloc(size + 1);
	if (dup == NULL)
		return (NULL);
	c = 0;
	while (src[c] != '\0')
	{
		dup[c] = src[c];
		c++;
	}
	dup[c] = '\0';
	return (dup);
}

// int	main(void)
// {
// 	char	array[] = "duplicating a string using malloc and stuff";
// 	char	*dup;

// 	dup = ft_strdup(array);
// 	printf("Original:  %s\n", array);
// 	printf("Duplicate: %s", dup);
// 	free (dup);
// 	return (0);
// }
