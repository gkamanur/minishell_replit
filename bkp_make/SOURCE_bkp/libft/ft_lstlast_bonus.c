/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:25:51 by robello-          #+#    #+#             */
/*   Updated: 2024/12/03 20:05:40 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// int main()
// {
// 	t_list *head = malloc(sizeof(t_list));
// 	t_list *second = malloc(sizeof(t_list));
// 	t_list *third = malloc(sizeof(t_list));
// 	t_list *fourth = malloc(sizeof(t_list));
// 	head->content = ft_strdup("First");
// 	head->next = second;
// 	second->content = ft_strdup("Second");
// 	second->next = third;
// 	third->content = ft_strdup("Third");
// 	third->next = fourth;
// 	fourth->content = ft_strdup("Fourth");
// 	fourth->next = NULL;
// 	printf("Linked List: ");
// 	t_list *current = head;
// 	while (current)
// 	{
// 		printf("%s -> ", (char *)current->content);
// 		current = current->next;
// 	}
// 	printf("NULL\n");
// 	t_list *last = ft_lstlast(head);
// 	if (last)
// 		printf("Last element: %s\n", (char *)last->content);
// 	else
// 		printf("The list is empty.\n");
// 	while (head)
// 	{
// 		t_list *temp = head;
// 		head = head->next;
// 		free(temp);
// 	}
// }
