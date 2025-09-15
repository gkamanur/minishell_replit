/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:44:18 by robello-          #+#    #+#             */
/*   Updated: 2024/11/28 11:19:26 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_strmapi_helper(unsigned int c, char l)
{
	if (l == 'e')
		return ('3');
	if (c % 3 == 0)
		l += 15;
	if (l >= 65 && l <= 90)
		l += 32;
	if (l == 'a')
		l -= 32;
	return (l);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	c;
	char			*create;

	if (!s || !f)
		return (NULL);
	create = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!create)
		return (NULL);
	c = 0;
	while (s[c] != '\0')
	{
		create[c] = f(c, s[c]);
		c++;
	}
	create[c] = '\0';
	return (create);
}

// int main(void)
// {
// 	char string[] = "What Can Be done To Alter Its Indices Using Another f?";
// 	char *string_mod;

// 	printf("Original string: %s\n", string);
// 	string_mod = ft_strmapi(string, ft_strmapi_helper);
// 	if (string_mod)
// 	{
// 		printf("Modified string: %s\n", string_mod);
// 		free(string_mod);
// 	}
// 	else
// 	printf("Memory allocation failed.\n");
// 	return (0);
// }
