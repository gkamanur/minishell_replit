/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:11:24 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:56:45 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// int	main(void)
// {
// 	int	digit;

// 	digit = ft_isdigit('5');
// 	printf("%d	", digit);
// 	digit = ft_isdigit('x');
// 	printf("%d	", digit);
// 	return (0);
// }
