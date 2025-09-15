/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:43:46 by robello-          #+#    #+#             */
/*   Updated: 2024/12/11 23:15:24 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
		{
			words++;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	return (words);
}

static void	ft_free_strings(char **new_strings)
{
	int	i;

	i = 0;
	while (new_strings[i])
	{
		free(new_strings[i]);
		i++;
	}
	free(new_strings);
}

static char	*ft_create_string(const char *s, char c)
{
	int		len_word;
	char	*new_string;
	int		i;

	len_word = 0;
	while (s[len_word] && s[len_word] != c)
		len_word++;
	new_string = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!new_string)
		return (NULL);
	i = 0;
	while (i < len_word)
	{
		new_string[i] = s[i];
		i ++;
	}
	new_string[len_word] = '\0';
	return (new_string);
}

static int	ft_allocate_words(const char *s, char **new_strings, char c)
{
	int	st_cnt;

	st_cnt = 0;
	while (*s)
	{
		if (*s != c)
		{
			new_strings[st_cnt] = ft_create_string(s, c);
			if (!new_strings[st_cnt])
			{
				ft_free_strings(new_strings);
				return (-1);
			}
			st_cnt++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (st_cnt);
}

char	**ft_split(const char *s, char c)
{
	int		words;
	int		i;
	char	**new_strings;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	new_strings = (char **) malloc (sizeof(char *) * (words + 1));
	if (!new_strings)
		return (NULL);
	i = ft_allocate_words(s, new_strings, c);
	if (i == -1)
		return (NULL);
	new_strings[i] = 0;
	return (new_strings);
}

// int	main(void)
// {
// 	char	string[] = "  Hello there, this is  a  splitted string    test.  ";
// 	char	c;
// 	char	**splitted;
// 	int		i;

// 	c = ' ';
// 	printf("\n\"%s\"\n", string);
// 	splitted = ft_split(string, c);
// 	i = 0;
// 	while (splitted[i])
// 	{
// 		printf("Word %d: \"%s\"\n", i + 1, splitted[i]);
// 		free(splitted[i]);
// 		i++;
// 	}
// 	free(splitted);
// 	return (0);
// }
