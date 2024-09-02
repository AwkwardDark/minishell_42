/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:24:22 by pierre            #+#    #+#             */
/*   Updated: 2024/09/02 14:05:05 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	returns pointer to the opening parenthesis corresponding 
	exemple: cmd && (cmd || cmd) points to  (
*/
t_token	*ignore_parenthesis(t_token *token)
{
	int		i;
	t_token	*temp;

	temp = token->prev;
	i = 0;
	while (temp->token_type != O_PAR && i == 0)
	{
		if (temp->token_type == C_PAR)
			i++;
		if (temp->token_type == O_PAR)
			i--;
		temp = temp->prev;
	}
	return (temp);
}

/*  
	retruns 1 one the first node that has the priority 
	priority 3 is && or ||
	priority 2 is |
	priority 1 is cmd should always return (1)
*/
t_token	*contains_priority(t_token *token, int priority)
{
	int	i;

	while (token != NULL)
	{
		if (token->token_type == C_PAR)
			token = ignore_parenthesis(token->prev);
		if (priority == 3)
		{
			if (token->token_type == AND || token->token_type == OR)
				return (token);
		}
		else if (priority == 2)
		{
			if (token->token_type == PIPE)
				return (token);
		}
		token = token->prev;
	}
	return (NULL);
}

// displays the tree in the following format (node, left child, right child)
void	display_btree(t_btree *tree)
{
	if (tree == NULL)
		return ;
	else if (tree->left_child == NULL && tree->right_child == NULL)
		display_type(tree->token->token_type);
	else
	{
		printf("( ");
		display_type(tree->token->token_type);
		printf(", ");
		display_btree(tree->left_child);
		printf(", ");
		display_btree(tree->right_child);
		printf(" )");
	}
}
