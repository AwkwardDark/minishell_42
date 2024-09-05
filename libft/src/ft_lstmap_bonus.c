/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:21:53 by pierre            #+#    #+#             */
/*   Updated: 2024/08/30 15:50:08 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;
	t_list	**og;

	og = &lst;
	new = NULL;
	while (lst != NULL)
	{
		temp = ft_lstnew_b((*f)(lst->content), 0);
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back_b(&new, temp);
		lst = lst->next;
	}
	ft_lstclear(og, del);
	return (new);
}
