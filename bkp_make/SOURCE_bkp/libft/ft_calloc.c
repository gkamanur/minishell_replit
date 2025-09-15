/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:03:10 by robello-          #+#    #+#             */
/*   Updated: 2024/11/28 14:10:23 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*new_block;
	size_t			new_size;
	int				c;

	c = 0;
	new_size = nmemb * size;
	new_block = malloc(new_size);
	if (!(new_block))
		return (NULL);
	ft_memset(new_block, c, new_size);
	return (new_block);
}

// int main(void)
// {
// 	char *array;
// 	int *array_int;
// 	size_t a;
// 	size_t nmemb;

// 	a = 0;
// 	nmemb = 10;
// 	array = ft_calloc(nmemb, sizeof(char));
// 	if (array == NULL)
// 		printf("Error!\n");
// 	else
// 	{
// 		while (a < nmemb)
// 		{
// 			printf("%d ", array[a]);
// 			a++;
// 		}
// 	printf("\n");
// 	}
// 	array_int = ft_calloc(nmemb, sizeof(int));
// 	a = 0;
// 	if (array_int == NULL)
// 		printf("Error!\n");
// 	else
// 	{
// 		while (a < nmemb)
// 		{
// 			printf("%d ", array_int[a]);
// 			a++;
// 		}
// 		printf("\n");
// 	}
// 	free(array);
// 	free(array_int);
// 	return (0);
// }
