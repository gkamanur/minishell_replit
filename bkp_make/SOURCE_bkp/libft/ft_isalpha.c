/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:50:34 by robello-          #+#    #+#             */
/*   Updated: 2024/11/27 20:09:04 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// int	main(void)
// {
// 	int	alpha;

// 	alpha = ft_isalpha('t');
// 	printf("%d	", alpha);
// 	alpha = ft_isalpha('8');
// 	printf("%d	", alpha);
// 	return (0);
// }
