/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:07:53 by robello-          #+#    #+#             */
/*   Updated: 2025/07/18 01:17:37 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(const char *s, int fd)
{
	int	i;

	if (s != NULL)
	{
		i = 0;
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

// int	main(void)
// {
// 	char	string[] = "Display this string using fd in function, etc.\n";
// 	char	string1[] = "";
// 	char	string11[] = "\n";
// 	char	string2[] = "12345780987654\n";
// 	char	string3[] = "\nEnd Of the line 12365.\n";

// 	ft_putstr_fd(string, 1);
// 	ft_putstr_fd(string1, 1);
// 	ft_putstr_fd(string11, 1);
// 	ft_putstr_fd(string2, 1);
// 	ft_putstr_fd(string3, 1);
// 	return (0);
// }
