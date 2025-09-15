/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robello- <robello-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:24:58 by robello-          #+#    #+#             */
/*   Updated: 2024/12/03 11:34:05 by robello-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// int	main(void)
// {
// 	t_list	*new_node;
// 	t_list	*new_new;

// 	char	*content = "Creating a new NODE with function ft_lstnew.";
// 	new_node = ft_lstnew(content);
// 	if (!new_node)
// 		return (1);
// 	printf("Content of the new NODE is: \"%s\"", ((char *)new_node->content));
// 	new_new = ft_lstnew("Also another new NODE'S content");
// 	if (!new_new)
// 		return (1);
// 	printf("\nContent of the new NODE is: \"%s\"", ((char *)new_new->content));
// 	free(new_node);
// 	free(new_new);
// 	return (0);
// }
