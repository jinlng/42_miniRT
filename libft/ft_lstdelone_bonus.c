/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:02:28 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:56:54 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*void del(void *content) { (void)content; }
int main(void)
{
	t_list *node = ft_lstnew("Test");
	printf("before: %p\n", (void*)node);
	ft_lstdelone(node, del);
	printf("deleted\n");
}*/
