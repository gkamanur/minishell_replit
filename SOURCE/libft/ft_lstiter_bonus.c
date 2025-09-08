/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:50:52 by robello-          #+#    #+#             */
/*   Updated: 2024/12/03 16:18:43 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

void	ft_multiply_node_by(void *content)
{
	int	*value;

	value = (int *)content;
	*value *= 5;
}

// int main(void)
// {
// 	t_list	*node1 = malloc(sizeof(t_list));
// 	t_list	*node2 = malloc(sizeof(t_list));
// 	t_list	*node3 = malloc(sizeof(t_list));
// 	t_list	*node4 = malloc(sizeof(t_list));
// 	t_list	*temp;
// 	int		i;
//
// 	int *a = malloc(sizeof(int *));
// 	int *b = malloc(sizeof(int *));
// 	int *c = malloc(sizeof(int));
// 	int *d = malloc(sizeof(int));
// 	*a = 10;
// 	*b = 20;
// 	*c = 30;
// 	*d = 100;
// 	node1->content = a;
// 	node1->next = node2;
// 	node2->content = b;
// 	node2->next = node3;
// 	node3->content = c;
// 	node3->next = node4;
// 	node4->content = d;
// 	node4->next = NULL;
// 	printf("Original values:\n");
// 	temp = node1;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Node %d:  %d\n", i + 1, *((int *)temp->content));
// 		temp = temp->next;
// 	}
// 	ft_lstiter(node1, ft_multiply_node_by);
// 	printf("\nValues after Iterating using (f)function:\n");
// 	temp = node1;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Node %d:  %d\n", i + 1, *((int *)temp->content));
// 		temp = temp->next;
// 	}
// 	free(a);
// 	free(b);
// 	free(c);
// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return 0;
// }
