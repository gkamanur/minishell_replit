/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:06:48 by robello-          #+#    #+#             */
/*   Updated: 2024/11/25 17:22:39 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
// int	main(void)
// {
// 	char	letter;

// 	letter = 'r';
// 	ft_putchar_fd(letter, 1);
// 	letter = 's';
// 	ft_putchar_fd(letter, 1);
// 	letter = '3';
// 	ft_putchar_fd(letter, 1);
// 	letter = 'c';
// 	ft_putchar_fd(letter, 1);
// 	letter = ' ';
// 	ft_putchar_fd(letter, 1);
// 	return(0);
// }