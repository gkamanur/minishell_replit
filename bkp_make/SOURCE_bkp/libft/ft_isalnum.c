/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:31:22 by robello-          #+#    #+#             */
/*   Updated: 2024/11/24 14:55:37 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

// int	main(void)
// {
// 	int	aln;

// 	aln = ft_isalnum('y');
// 	printf("%d\n", aln);
// 	aln = ft_isalnum('7');
// 	printf("%d\n", aln);
// 	aln = ft_isalnum('%');
// 	printf("%d\n", aln);
// 	aln = ft_isalnum(' ');
// 	printf("%d\n", aln);
// 	return (0);
// }
