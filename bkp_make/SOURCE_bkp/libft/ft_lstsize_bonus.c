/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:57:06 by robello-          #+#    #+#             */
/*   Updated: 2024/12/03 11:25:37 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// int	main(void)
// {
// 	t_list	*head = NULL;
// 	t_list	*second = NULL;
// 	t_list	*third = NULL;
// 	t_list	*fourth = NULL;
// 	int		size;

// 	head = (t_list *)malloc(sizeof(t_list));
// 	second = (t_list *)malloc(sizeof(t_list));
// 	third = (t_list *)malloc(sizeof(t_list));
// 	fourth = (t_list *)malloc(sizeof(t_list));
// 	if (head == NULL || second == NULL || third == NULL || fourth == NULL)
// 	{
// 		printf("Memory allocation failed.\n");
// 		return (1);
// 	}
// 	third->content = "Third";
// 	head->content = "Counting how many nodes we have in this 'list'.";
// 	head->next = second;
// 	second->next = third;
// 	third->next = fourth;
// 	fourth->next = NULL;
// 	size = ft_lstsize(head);
// 	printf("The size of the list 'lst' is: %d nodes.\n", size);
// 	printf("The content of 'head' is: %s", (char *)head->content);
// 	free(head);
// 	free(second);
// 	free(third);
// 	free(fourth);
// 	return (0);
// }
