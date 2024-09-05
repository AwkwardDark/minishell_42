/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:21:58 by pierre            #+#    #+#             */
/*   Updated: 2024/08/30 14:44:30 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew_b(void *content, int len)
{
	t_list	*liste;

	liste = (t_list *)malloc(sizeof(t_list));
	if (!liste)
		return (NULL);
	liste->content = content;
	liste->next = NULL;
	liste->len = len;
	return (liste);
}
