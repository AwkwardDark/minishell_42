/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:01:05 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/03 18:28:17 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_and_grammar(t_token *lst)
{
	if ((!lst->prev) || (lst->next->token_type == AND))
		return (1);
	return (0);
}

int ft_grammar_syntax(t_token *lst)
{
	t_token *current;

	current = lst;
	while (current != NULL)
	{
		// AND et OR
		if (current->token_type == AND || current->token_type == OR)
		{
			if (current->next)
			{
				if ((current->next->token_type == AND) || (current->next->token_type == OR) || (current->next->token_type == PIPE) || (current->next->token_type == C_PAR))
					return (printf("1\n"), 1);
			}
			if ((!current->next) || (!current->prev) || ((current->prev->token_type != WORD) && (current->prev->token_type != C_PAR)))
				return (printf("2\n"), 1);
		}
		// PIPE
		if (current->token_type == PIPE)
		{
			if (current->next)
			{
				if ((current->next->token_type == AND) || (current->next->token_type == OR) || (current->next->token_type == PIPE) || (current->next->token_type == C_PAR) || (current->next->token_type == O_PAR))
					return (printf("3\n"), 1);
			}
			if ((!current->next) || (!current->prev) || ((current->prev->token_type != WORD) && (current->prev->token_type != C_PAR)))
				return (printf("4\n"), 1);
		}
		// REDIR
		if ((current->token_type == IN_R) || (current->token_type == OUT_R) || (current->token_type == HEREDOC) || (current->token_type == APPEND))
		{
			if (current->next)
			{
				if (current->next->token_type != WORD)
					return (printf("5\n"), 1);
			}
			if ((!current->next) || (current->prev->token_type == C_PAR) || (current->prev->token_type == IN_R) || (current->prev->token_type == OUT_R) || (current->prev->token_type == HEREDOC) || (current->prev->token_type == APPEND))
				return (printf("6\n"), 1);
		}
		// WORD
		if (current->token_type == WORD)
		{
			if (current->next)
			{
				if (current->next->token_type == O_PAR)
					return (printf("7\n"), 1);
			}
			if (current->prev)
			{
				if (current->prev->token_type == C_PAR)
					return (printf("8\n"), 1);
			}
		}
		// Open Parenthesis
		if (current->token_type == O_PAR)
		{
			if (current->next)
			{
				if ((current->next->token_type == AND) || (current->next->token_type == OR) || (current->next->token_type == PIPE) || (current->next->token_type == C_PAR))
					return (printf("9\n"), 1);
			}
			if (current->prev)
			{
				if ((!current->next) || ((current->prev->token_type != AND) && (current->prev->token_type != OR) && (current->prev->token_type != O_PAR)))
					return (printf("10\n"), 1);
			}
		}
		// Close Parenthesis
		if (current->token_type == C_PAR)
		{
			if (current->next)
			{
				if ((current->next->token_type != AND) && (current->next->token_type != OR))
					return (printf("11\n"), 1);
			}
			if ((!current->prev) || (current->prev->token_type != WORD))
				return (printf("12\n"), 1);
		}
		current = current->next;
	}
	return (0);
}
