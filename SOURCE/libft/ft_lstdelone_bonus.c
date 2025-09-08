/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:24:11 by robello-          #+#    #+#             */
/*   Updated: 2024/12/03 11:35:15 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (lst->content)
		del(lst->content);
	free(lst);
}

// void	ft_delete_content(void *content)
// {
// 	free (content);
// }
// int main(void)
// {
// 	t_list *head = NULL;
// 	t_list *fir = NULL;
// 	t_list *se = NULL;
// 	t_list *thr = NULL;
// 	t_list *last = NULL;
// 	t_list *temp;
// 	int i;
// 	head = (t_list *)malloc(sizeof(t_list));
// 	fir = (t_list *)malloc(sizeof(t_list));
// 	se = (t_list *)malloc(sizeof(t_list));
// 	thr = (t_list *)malloc(sizeof(t_list));
// 	last = (t_list *)malloc(sizeof(t_list));
// 	if (!head || !fir || !se || !thr || !last)
// 	{
// 		printf("Memory allocation failed\n");
// 		return (1);
// 	}
// 	head->content = malloc(sizeof(int));
// 	*((int *)head->content) = 22;
// 	fir->content = malloc(sizeof(int));
// 	*((int *)fir->content) = 33;
// 	se->content = malloc(sizeof(int));
// 	*((int *)se->content) = 1010;
// 	thr->content = malloc(sizeof(int));
// 	*((int *)thr->content) = 55;
// 	last->content = malloc(sizeof(int));
// 	*((int *)last->content) = 66;
// 	head->next = fir;
// 	fir->next = se;
// 	se->next = thr;
// 	thr->next = last;
// 	last->next = NULL;
// 	printf("All nodes' contents:\n");
// 	temp = head;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Node %d: %d\n", i + 1, *((int *)temp->content));
// 		temp = temp->next;
// 		i++;
// 	}
// 	printf("\n");
// 	temp = head;
// 	while (temp->next != NULL)
// 	{
// 		if (temp->next == se)
// 		{
// 			temp->next = se->next;
// 			ft_lstdelone(se, ft_delete_content);
// 			break;
// 		}
// 		temp = temp->next;
// 	}
// 	printf("Remaining nodes after deleting one of them:\n");
// 	temp = head;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Node %d: %d\n", i + 1, *((int *)temp->content));
// 		temp = temp->next;
// 		i++;
// 	}
// 	while (head)
// 	{
// 		temp = head->next;
// 		free(head->content);
// 		free(head);
// 		head = temp;
// 	}
// 	return 0;
// }
