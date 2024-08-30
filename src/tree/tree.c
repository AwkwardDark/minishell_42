/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:21:21 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/30 19:17:39 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates a leaf
t_btree	*init_tree(t_token *token, t_btree *left, t_btree *right)
{
	t_btree *tree;

	tree = (struct s_btree *)malloc(sizeof(struct s_btree));
	if (!tree)
		return (NULL);
	tree->token = token;
	tree->left_child = left;
	tree->right_child = right;
}

/*  
	retruns 1 one the first node that has the priority 
	priority 3 is && or ||
	priority 2 is |
	priority 1 is cmd should always return (1)
*/
static t_token	*contains_priority(t_token *token, int priority)
{
	while (token != NULL)
	{
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

t_token	*get_endlst(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

t_btree	*create_tokentree(t_token **token)
{
	t_token *temp;
	t_token *right;
	t_token *left;

	temp = get_endoflst(*token);
	if (contains_priority(temp, 3))
	{
		temp = contains_priority(temp, 3);
		right= temp->next;
		left= temp->prev;
		left->next = NULL;
		return (init_tree(temp, create_tokentree(&left), create_tokentree(&right)));
	}
	else if (contains_is_priority(temp, 2))
	{
		temp = contains_priority(temp, 3);
		right= temp->next;
		left= temp->prev;
		left->next = NULL;
		return (init_tree(temp, create_tokentree(&left), create_tokentree(&right)));
	}
	return (init_tree(token, NULL, NULL));
}
