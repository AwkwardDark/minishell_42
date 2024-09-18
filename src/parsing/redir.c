/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:50:41 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/18 20:18:34 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It deletes the tken type word after a redirection and saves it inside the
token structure, this technique will optimise execution*/
void	ft_redir_check(t_token **lst)
{
	t_token	*current;
	t_token	*delete;

	current = *lst;
	while (current)
	{
		if ((current->token_type == R_IN) || (current->token_type == R_OUT) || \
			(current->token_type == HEREDOC) || (current->token_type == APPEND))
		{
			delete = current->next;
			current->redir = ft_strdup(delete->content);
			current->quote_flag = delete->quote_flag;
			if (delete->next)
			{
				delete->next->prev = current;
				current->next = delete->next;
			}
			else
				current->next = NULL;
			free(delete->content);
			free(delete);
		}
		current = current->next;
	}
}
