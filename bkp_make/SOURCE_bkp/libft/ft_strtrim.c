/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:50:04 by robello-          #+#    #+#             */
/*   Updated: 2024/12/20 14:32:17 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*trimmed;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]))
		i--;
	trimmed = ft_substr(s1, 0, i + 1);
	return (trimmed);
}

// int main()
// {
// 	char	s[] = " \t\n\t\nThis is   not a clean string.\t  \n";
// 	char	s1[] = "";
// 	char	s2[] = "123					";
// 	char	s3[] = " \f\n\r\v\t ";
// 	char	s4[] = " \t\n\t\nClean string.\t  \n";
// 	char	s5[] = "	R	\v";
// 	char	s6[] = "  1 2  3		";
// 	char	*set = " \f\n\r\v\t";
// 	char	*trimmed;
// 	char	*trimmed1;
// 	char	*trimmed2;
// 	char	*trimmed3;
// 	char	*trimmed4;
// 	char	*trimmed5;
// 	char	*trimmed6;

// 	printf("Original string: \"%s\"\n", s);
// 	trimmed = ft_strtrim(s, set);
// 	printf("Trimmed string1 : \"%s\"\n\n\n", trimmed);
// 	free(trimmed);

// 	printf("Original string: \"%s\"\n", s1);
// 	trimmed1 = ft_strtrim(s1, set);
// 	printf("Trimmed string2 : \"%s\"\n\n\n", trimmed1);
// 	free(trimmed1);

// 	printf("Original string: \"%s\"\n", s2);
// 	trimmed2 = ft_strtrim(s2, set);
// 	printf("Trimmed string3 : \"%s\"\n\n\n", trimmed2);
// 	free(trimmed2);

// 	printf("Original string: \"%s\"\n", s3);
// 	trimmed3 = ft_strtrim(s3, set);
// 	printf("Trimmed string4 : \"%s\"\n\n\n", trimmed3);
// 	free(trimmed3);

// 	printf("Original string: \"%s\"\n", s4);
// 	trimmed4 = ft_strtrim(s4, set);
// 	printf("Trimmed string5 : \"%s\"\n\n\n", trimmed4);
// 	free(trimmed4);

// 	printf("Original string: \"%s\"\n", s5);
// 	trimmed5 = ft_strtrim(s5, set);
// 	printf("Trimmed string6 : \"%s\"\n\n\n", trimmed5);
// 	free(trimmed5);

// 	printf("Original string: \"%s\"\n", s6);
// 	trimmed6 = ft_strtrim(s6, set);
// 	printf("Trimmed string7 : \"%s\"\n\n\n", trimmed6);
// 	free(trimmed6);
// 	return 0;
// }
