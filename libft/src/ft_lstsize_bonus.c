/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:22:01 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:27:46 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		n;
	t_list	*temp;

	temp = lst;
	n = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		n++;
	}
	return (n);
}
