/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello <robello-@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:31:15 by robello-          #+#    #+#             */
/*   Updated: 2025/07/30 17:13:49 by robello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

// int	main(void)
// {
// 	//t_list	**lst;
// 	t_list	*head = NULL;
// 	t_list	*second = NULL;
// 	t_list	*third = NULL;
// 	t_list	*fourth = NULL;
// 	t_list *fifth = NULL;
// 	t_list *temp;
// 	int		cnt;

// 	head = (t_list *)malloc(sizeof(t_list));
// 	second = (t_list *)malloc(sizeof(t_list));
// 	third = (t_list *)malloc(sizeof(t_list));
// 	fourth = (t_list *)malloc(sizeof(t_list));
// 	if (!(head && second && third && fourth))
// 		return (1);
// 	head->next = second;
// 	second->next = third;
// 	third->next = fourth;
// 	fourth->next = NULL;
// 	cnt = 0;
// 	temp = head;
// 	while (temp)
// 	{
// 		temp = temp->next;
// 		cnt++;
// 	}
// 	printf("Number of Nodes: %d\n", cnt);
// 	fifth = (t_list *)malloc(sizeof(t_list));
// 	if (!(fifth))
// 		return (1);
// 	fifth->next = NULL;
// 	ft_lstadd_back(&head, fifth);
// 	temp = head;
// 	cnt = 0;
// 	while (temp)
// 	{
// 		temp = temp->next;
// 		cnt++;
// 	}
// 	printf("Number of Nodes after using ft_lstadd_back: %d\n", cnt);
// 	while (head)
// 	{
// 		temp = head->next;
// 		free(head);
// 		head = temp;
// 	}
// 	return (0);
// }
