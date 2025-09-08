/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:04:47 by robello-          #+#    #+#             */
/*   Updated: 2024/12/04 15:34:45 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			if (content)
				del(content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

// void	*ft_string_reverse(void *content)
// {
// 	size_t	i;
// 	size_t	leng;
// 	char	*new_string;
// 	char	*temp_content;

// 	temp_content = (char *)content;
// 	leng = ft_strlen(temp_content);
// 	new_string = (char *)malloc(sizeof(char) * (leng + 1));
// 	if (!new_string)
// 		return (NULL);
// 	i = 0;
// 	while (i < leng)
// 	{
// 		new_string[i] = temp_content[leng - i -1];
// 		i++;
// 	}
// 	new_string[i] = '\0';
// 	return (new_string);
// }

// void	ft_delete_content(void *content)
// {
// 	free (content);
// }

// int main(void)
// {
// 	t_list	*node1 = malloc(sizeof(t_list));
// 	t_list	*node2 = malloc(sizeof(t_list));
// 	t_list	*node3 = malloc(sizeof(t_list));
// 	t_list	*node4 = malloc(sizeof(t_list));
// 	t_list	*node5 = malloc(sizeof(t_list));
// 	t_list	*new_map;
// 	t_list	*temp;
// 	int		i;

// 	node1->content = ft_strdup("GNITAERC");
// 	node1->next = node2;
// 	node2->content = ft_strdup("A");
// 	node2->next = node3;
// 	node3->content = ft_strdup("WEN");
// 	node3->next = node4;
// 	node4->content = ft_strdup("TSIL");
// 	node4->next = node5;
// 	node5->content = ft_strdup("!!");
// 	node5->next = NULL;
// 	if (!node1 || !node2 || !node3 || !node4 || !node5)
// 	{
// 		printf("Memory allocation failed\n");
// 		return (1);
// 	}
// 	temp = node1;
// 	i = 0;
// 	while(temp)
// 	{
// 		printf("Content of node %d:  \"%s\"\n", i + 1, ((char *)temp->content));
// 		temp = temp->next;
// 		i++;
// 	}
// 	new_map = ft_lstmap(node1, ft_string_reverse, ft_delete_content);
// 	printf("\nNodes' values  after using ft_lstmap:\n");
// 	temp = new_map;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Node %d: \"%s\"\n", i + 1, ((char *)temp->content));
// 		temp = temp->next;
// 		i++;
// 	}

// 	ft_lstclear(&node1, ft_delete_content);
// 	ft_lstclear(&new_map, ft_delete_content);
// 	return 0;
// }

//
// int main(void)
// {
// 	t_list *node1 = malloc(sizeof(t_list));
// 	t_list *node2 = malloc(sizeof(t_list));
// 	t_list *node3 = malloc(sizeof(t_list));
// 	t_list *node4 = malloc(sizeof(t_list));
// 	int		i;

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
// 	t_list *temp = node1;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Node %d:  %d\n", i + 1, *((int *)temp->content));
// 		temp = temp->next;
// 	}
// 	ft_lstmap(node1, (void*)ft_multiply_node_by, ft_delete_content);
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