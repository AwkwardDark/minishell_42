/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:57:07 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/11 16:59:10 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wildcard(t_token *lst)
{
	t_token	*current;
	
	current = lst;
	while(current)
	{
		if (current->wildcard)
			/...
		current = current->next;
	}
}
