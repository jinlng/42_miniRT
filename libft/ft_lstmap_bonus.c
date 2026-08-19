/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:03:29 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:53:24 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*content;

	if (!f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
/*
void	*dup(void *content)
{
	return (ft_strdup((char*)content));
}

void	del(void *content)
{
	free(content);
}

int main(void)
{
	t_list *head = ft_lstnew("A");
	ft_lstadd_back(&head, ft_lstnew("B"));
	t_list *new = ft_lstmap(head, dup, del);
	for (t_list *p = new; p; p = p->next)
		printf("%s ", (char*)p->content);
	printf("\n");
	ft_lstclear(&new, del);
}
*/
