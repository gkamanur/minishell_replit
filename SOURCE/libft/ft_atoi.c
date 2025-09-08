/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:31:12 by robello-          #+#    #+#             */
/*   Updated: 2025/07/17 17:54:10 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static int	ft_check_min_max(long nbr, int sign)
// {
// 	if (sign == 1 && nbr > INT_MAX)
// 		return (1);
// 	if (sign == -1 && nbr > (long)INT_MAX + 1)
// 		return (1);
// 	return (0);
// }

long	ft_atoi(const char *str)
{
	long	nbr;
	int		sign;
	int		i;

	nbr = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

// int	ft_atoi(const char *str)
// {
// 	long	i;
// 	int		sign;
// 	long	nb;

// 	i = 0;
// 	nb = 0;
// 	sign = 1;
// 	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		if (nb > (LONG_MAX - (str[i] - '0')) / 10)
// 		{
// 			if (sign == 1)
// 				return (-1);  // Return -1 for positive overflow
// 			else
// 				return (0);   // Return 0 for negative overflow
// 		}
// 		nb = nb * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	return ((int)(sign * nb));
// }

// int	main(void)
// {
// 	int	a;

// 	a = ft_atoi(" \n\v\t 90{}[]4568-087");
// 	printf("%d\n", a);
// 	a = atoi(" \n\v\t 90{}[]4568-087");
// 	printf("%d\n\n", a);
// 	a = ft_atoi("  -*/+98745[]{}-=-+344984efds");
// 	printf("%d\n", a);
// 	a = atoi("  -*/+98745[]{}-=-+344984efds");
// 	printf("%d\n\n", a);
// 	a = ft_atoi("   -987044984");
// 	printf("%d\n", a);
// 	a = atoi("   -987044984");
// 	printf("%d\n", a);
// 	a = ft_atoi("");
// 	printf("%d\n", a);
// 	a = atoi("");
// 	return (0);
// }
