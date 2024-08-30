/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:21:21 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/30 18:30:09 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates a leaf
t_btree	*init_tree(t_token *token)
{
	t_btree *tree;

	tree = (struct s_btree *)malloc(sizeof(struct s_btree));
	if (!tree)
		return (NULL);
	tree->token = token;
	tree->left_child = NULL;
	tree->right_child = NULL;
}

static int	contains_priority(t_token *token, int priority)
{
	while (token != NULL)
	{
		if (priority == 3)
		{
			if (token->token_type == AND || token->token_type == OR)
				return (1);
			else
				return (0);
		}
		else if (priority == 2)
		{
			if (token->token_type == PIPE)
				return (1);
			else
				return (0);
		}
		token = token->prev; 
	}
	return (1);
}

t_token	cpy_token(t_token *token, int priority)
{

}

static t_env *find_priority(t_token *token, int priority)
{
	if (!token)
		fprintf(stderr, "Error in find priority");
	else
	{
		while (token != NULL)
		{
			if (is_priority(token, ))
				// return ();
			token = token->prev;
		}
		return (NULL);
	}
}

t_btree	*create_tokentree(t_token *token)
{
	t_token *temp;

	if (contains_priority(token, 3))
	{
		temp = init_tree();
		return (create_tokentree());
	}
	if (contains_is_priority)
		return (init_tree(token));
}
