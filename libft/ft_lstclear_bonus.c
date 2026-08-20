/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:02:43 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:56:45 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

/*void del(void *content) { (void)content; }
int main(void)
{
	t_list *head = ft_lstnew("A");
	ft_lstadd_back(&head, ft_lstnew("B"));
	ft_lstadd_back(&head, ft_lstnew("C"));
	printf("before: %p\n", (void*)head);
	ft_lstclear(&head, del);
	printf("after: %p\n", (void*)head);
}*/
