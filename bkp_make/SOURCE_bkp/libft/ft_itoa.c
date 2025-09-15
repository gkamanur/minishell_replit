/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:43:33 by robello-          #+#    #+#             */
/*   Updated: 2024/11/28 14:16:06 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_create_string(char *str, int nbr, int n, int len)
{
	if (nbr < 0)
		nbr = -nbr;
	str[len] = '\0';
	while (len > 0)
	{
		str[len - 1] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		nbr;
	char	*str;

	if (n == -2147483648)
		return (str = ft_strdup("-2147483648"));
	if (n == 0)
		return (str = ft_strdup("0"));
	len = 0;
	nbr = n;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	if (n < 0)
		len = len + 1;
	nbr = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_create_string(str, nbr, n, len);
	return (str);
}

// int main()
// {
// 	printf("\"%s\"\n", ft_itoa(123));
// 	printf("\"%s\"\n", ft_itoa(-123));
// 	printf("\"%s\"\n", ft_itoa(0));
// 	printf("\"%s\"\n", ft_itoa(2147483647));
// 	printf("\"%s\"\n", ft_itoa(-2147483648));
// 	printf("\"%s\"\n", ft_itoa(-1456));
// 	printf("\"%s\"\n", ft_itoa(-4526));
// 	printf("\"%s\"\n", ft_itoa(0));
// 	printf("\"%s\"\n", ft_itoa(2147483647));
// 	printf("\"%s\"\n", ft_itoa(-2147483648));
// 	return (0);
// }