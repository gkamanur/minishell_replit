/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:03:36 by robello-          #+#    #+#             */
/*   Updated: 2024/12/03 11:29:01 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

// int	main (void)
// {
// 	t_list	*lst;
// 	t_list	*new_front;
// 	t_list	*second;
// 	t_list	*third;
// 	t_list	*temp;
// 	lst = NULL;

// 	new_front = (t_list *)malloc(sizeof(t_list));
// 	second = (t_list *)malloc(sizeof(t_list));
// 	third = (t_list *)malloc(sizeof(t_list));
// 	if (!new_front || !second)
// 		return (1);
// 	new_front->content = "first node";
// 	second->content = "second node";
// 	third->content = "third node";
// 	ft_lstadd_front(&lst, new_front);
// 	ft_lstadd_front(&lst, second);
// 	ft_lstadd_front(&lst, third);
// 	temp = lst;
// 	while (temp)
// 	{
// 		printf("%s -> ",(char *)temp->content);
// 		temp = temp->next;
// 	}
// 	while(lst)
// 	{
// 		temp  = lst;
// 		lst = lst->next;
// 		free(temp);
// 	}
// 	printf("NULL\n");
// 	return (0);
// }
