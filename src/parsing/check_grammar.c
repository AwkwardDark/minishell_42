/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:01:05 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/04 16:51:31 by pajimene         ###   ########.fr       */
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
			(current->prev->token_type == IN_R) || \
				(current->prev->token_type == OUT_R) || \
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

static int	ft_parenthesis_grammar(t_token *current)
{
	if ((current->next) && (current->token_type == O_PAR))
	{
		if ((current->next->token_type == AND) || \
			(current->next->token_type == OR) || \
				(current->next->token_type == PIPE) || \
					(current->next->token_type == C_PAR))
			return (1);
	}
	if ((current->prev) && (current->token_type == O_PAR))
	{
		if ((!current->next) || ((current->prev->token_type != AND) && \
			(current->prev->token_type != OR) && \
				(current->prev->token_type != O_PAR)))
			return (1);
	}
	if ((current->next) && (current->token_type == C_PAR))
	{
		if ((current->next->token_type != AND) && \
			(current->next->token_type != OR))
			return (1);
	}
	if (((!current->prev) || (current->prev->token_type != WORD)) && \
		(current->token_type == C_PAR))
		return (1);
	return (0);
}

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
		if ((current->token_type == IN_R) || (current->token_type == OUT_R) || \
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
