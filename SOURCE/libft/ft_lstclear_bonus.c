/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:13:05 by robello-          #+#    #+#             */
/*   Updated: 2024/12/03 11:16:08 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

// void	ft_delete_cont(void *content)
// {
// 	free (content);
// }
// int main(void)
// {
// 	t_list *fir = NULL;
// 	t_list *se = NULL;
// 	t_list *thr = NULL;
// 	t_list *fou = NULL;
// 	t_list *last = NULL;
// 	t_list *temp;
// 	int i;
// 	fir = (t_list *)malloc(sizeof(t_list));
// 	se = (t_list *)malloc(sizeof(t_list));
// 	thr = (t_list *)malloc(sizeof(t_list));
// 	fou = (t_list *)malloc(sizeof(t_list));
// 	last = (t_list *)malloc(sizeof(t_list));
// 	if (!fir || !se || !thr || !last || !fou)
// 	{
// 		printf("Memory allocation failed\n");
// 		return (1);
// 	}
// 	fir->content = malloc(sizeof(int));
// 	*((int *)fir->content) = 33;
// 	se->content = malloc(sizeof(int));
// 	*((int *)se->content) = 1010;
// 	thr->content = malloc(sizeof(int));
// 	*((int *)thr->content) = 55;
// 	fou->content = malloc(sizeof(int));
// 	*((int *)fou->content) = 80;
// 	last->content = malloc(sizeof(int));
// 	*((int *)last->content) = 66;
// 	fir->next = se;
// 	se->next = thr;
// 	thr->next = fou;
// 	fou->next = last;
// 	last->next = NULL;
// 	printf("All nodes' contents:\n");
// 	temp = fir;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Node %d: %d\n", i + 1, *((int *)temp->content));
// 		temp = temp->next;
// 		i++;
// 	}
// 	printf("\n");
// 	t_list *node_to_delete_from = thr;
// 	temp = fir;
// 	while (temp->next != NULL)
// 	{
// 		if (temp->next == node_to_delete_from)
// 		{
// 			temp->next = NULL;
// 			break;
// 		}
// 		temp = temp->next;
// 	}
// 	ft_lstclear(&node_to_delete_from, ft_delete_cont);
// 	printf("Remaining nodes after deleting from a random node:\n");
// 	temp = fir;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Node %d: %d\n", i + 1, *((int *)temp->content));
// 		temp = temp->next;
// 		i++;
// 	}
// 	ft_lstclear(&fir, ft_delete_cont);
// 	return 0;
// }
