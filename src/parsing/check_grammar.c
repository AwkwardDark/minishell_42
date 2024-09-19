/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:01:05 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/18 20:09:58 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_and_or_pipe_grammar(t_token *current)
{
	if (current->next)
	{
		if ((current->next->token_type == AND) || \
			(current->next->token_type == OR) || \
			(current->next->token_type == PIPE) || \
			(current->next->token_type == C_PAR))
			return (1);
	}
	if ((!current->next) || (!current->prev) || \
		((current->prev->token_type != WORD) && \
			(current->prev->token_type != C_PAR)))
		return (1);
	if ((current->token_type == PIPE) && (current->next))
	{
		if (current->next->token_type == O_PAR)
			return (1);
	}
	return (0);
}

static int	ft_redir_grammar(t_token *current)
{
	if (current->next)
	{
		if (current->next->token_type != WORD)
			return (1);
	}
	if (current->prev)
	{
		if ((current->prev->token_type == C_PAR) || \
			(current->prev->token_type == R_IN) || \
				(current->prev->token_type == R_OUT) || \
					(current->prev->token_type == HEREDOC) || \
						(current->prev->token_type == APPEND))
			return (1);
	}
	if (!current->next)
		return (1);
	return (0);
}

static int	ft_word_grammar(t_token *current)
{
	if (current->next)
	{
		if (current->next->token_type == O_PAR)
			return (1);
	}
	if (current->prev)
	{
		if (current->prev->token_type == C_PAR)
			return (1);
	}
	return (0);
}

static int	ft_parenthesis_grammar(t_token *curr)
{
	if ((curr->next) && (curr->token_type == O_PAR))
	{
		if ((curr->next->token_type == AND) || (curr->next->token_type == OR) \
			|| (curr->next->token_type == PIPE) || \
				(curr->next->token_type == C_PAR))
			return (1);
	}
	if ((curr->prev) && (curr->token_type == O_PAR))
	{
		if ((!curr->next) || ((curr->prev->token_type != AND) && \
			(curr->prev->token_type != OR) && \
				(curr->prev->token_type != O_PAR)))
			return (1);
	}
	if ((curr->next) && (curr->token_type == C_PAR))
	{
		if ((curr->next->token_type != AND) && (curr->next->token_type != OR) \
			&& (curr->next->token_type != C_PAR))
			return (1);
	}
	if (((!curr->prev) || ((curr->prev->token_type != WORD) && \
		(curr->prev->token_type != C_PAR))) && (curr->token_type == C_PAR))
		return (1);
	return (0);
}

/*It analyses the token tye of the node before and after the current one.
It checks that the grammar rules of bash are well respected*/
int	ft_grammar_syntax(t_token *lst, t_data *data)
{
	t_token	*current;

	current = lst;
	while (current)
	{
		data->syntax_error = current->content;
		if (current->token_type == AND || current->token_type == OR || \
			(current->token_type == PIPE))
			if (ft_and_or_pipe_grammar(current))
				return (1);
		if ((current->token_type == R_IN) || (current->token_type == R_OUT) || \
			(current->token_type == HEREDOC) || (current->token_type == APPEND))
			if (ft_redir_grammar(current))
				return (1);
		if ((current->token_type == O_PAR) || (current->token_type == C_PAR))
			if (ft_parenthesis_grammar(current))
				return (1);
		if (current->token_type == WORD)
			if (ft_word_grammar(current))
				return (1);
		current = current->next;
	}
	return (0);
}
