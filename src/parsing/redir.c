/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:50:41 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/05 14:46:50 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_check(t_token **lst)
{
	t_token	*current;
	t_token	*delete;

	current = *lst;
	while (current)
	{
		if ((current->token_type == IN_R) || (current->token_type == OUT_R) || \
			(current->token_type == HEREDOC) || (current->token_type == APPEND))
		{
			delete = current->next;
			current->redir = delete->content;
			if (delete->next)
			{
				delete->next->prev = current;
				current->next = delete->next;
			}
			else
				current->next = NULL;
			free(delete);
			
		}
		current = current->next;
	}
}
