/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:02 by robello-          #+#    #+#             */
/*   Updated: 2024/11/30 23:58:26 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_decode_helper(unsigned int a, char *s)
{
	if (a % 3 == 0)
		*s = ' ';
	if (*s >= 'a' && *s <= 'z')
		*s -= 32;
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	a;

	if (s == 0 || f == 0)
		return ;
	a = 0;
	while (s[a] != '\0')
	{
		f(a, &s[a]);
		a++;
	}
}

// int	main(void)
// {
// 	char	string[] = "Modifying the string, now it is clear!";
// 	printf("Original: \"%s\"\n", string);
// 	ft_striteri(string, ft_decode_helper);
// 	printf("After using 'ft_striteri': \"%s\"", string);
// 	return (0);
// }
