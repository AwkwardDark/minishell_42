/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:21:36 by pierre            #+#    #+#             */
/*   Updated: 2024/06/03 17:53:48 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp1;

	temp = *lst;
	while (temp != NULL)
	{
		temp1 = temp->next;
		ft_lstdelone(temp, del);
		temp = temp1;
	}
	*lst = NULL;
}
