/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:50:41 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/21 01:18:17 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_refresh_expand_struct(t_token *current, t_token *delete)
{
	current->wildcard = delete->wildcard;
	current->del_wild_flag = 0;
	current->old_redir = ft_strdup(delete->content);
	if (((current->token_type == R_IN) || (current->token_type == R_OUT) || \
		(current->token_type == APPEND)) && ft_count_exp(current->redir) > 0)
	{
		current->pre_expand = delete->pre_expand;
		current->exp_tab_len = delete->exp_tab_len;
	}
	else
	{
		current->pre_expand = NULL;
		current->exp_tab_len = 0;
	}
}

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
			current->heredoc_quote_flag = delete->heredoc_quote_flag;
			ft_refresh_expand_struct(current, delete);
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
