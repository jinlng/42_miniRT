/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaytsev <azaytsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:00:55 by azaytsev          #+#    #+#             */
/*   Updated: 2025/11/14 13:57:29 by azaytsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

/*int main(void) {
    t_list *head = NULL;

    printf("size (empty)      = %d\n", ft_lstsize(head));

    ft_lstadd_front(&head, ft_lstnew("A"));
    printf("size after A      = %d\n", ft_lstsize(head));

    ft_lstadd_front(&head, ft_lstnew("B"));
    printf("size after B,A    = %d\n", ft_lstsize(head));

    ft_lstadd_front(&head, ft_lstnew("C"));
    printf("size after C,B,A  = %d\n", ft_lstsize(head));

    while (head) {
        t_list *next = head->next;
        free(head);
        head = next;
    }
    return 0;
}*/
