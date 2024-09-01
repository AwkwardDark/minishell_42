/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:21:21 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/01 23:33:01 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates a leaf
t_btree	*init_btree(t_token *token, t_btree *left, t_btree *right)
{
	t_btree	*tree;

	tree = (struct s_btree *)malloc(sizeof(struct s_btree));
	if (!tree)
		return (NULL);
	tree->token = token;
	tree->left_child = left;
	tree->right_child = right;
	return (tree);
}

/* 
	free's all the binary tree (not the tokens list *)
*/
void	clr_btree(t_btree *tree)
{
	if (!tree)
		return ;
	if (!tree->left_child && !tree->right_child)
		free(tree);
	else
	{
		clr_btree(tree->left_child);
		clr_btree(tree->right_child);
	}
}

/* 
	TODO
	check for other free to do for char * content 
*/
t_token	*remove_parenthesis(t_token *token)
{
	t_token	*temp;

	if (token->token_type != C_PAR)
		return (token);
	temp = ignore_parenthesis(token);
	if (temp->prev == NULL)
	{
		temp = temp->next;
		free(temp->prev);
		temp->prev = NULL;
		while (temp->next->next != NULL)
			temp = temp->next;
		free(temp->next);
		temp->next = NULL;
		return (temp);
	}
	return (token);
}

/* 
	NEEDS Unit tests
*/
t_btree	*create_tokentree(t_token **token)
{
	t_token	*temp;
	t_token	*right;
	t_token	*left;

	temp = ft_lstlast(*token);
	temp = remove_parenthesis(temp);
	if (contains_priority(temp, 3))
	{
		temp = contains_priority(temp, 3);
		right = temp->next;
		right->prev = NULL;
		left = temp->prev;
		left->next = NULL;
		return (init_btree(temp, create_tokentree(&left), create_tokentree(&right)));
	}
	else if (contains_priority(temp, 2))
	{
		temp = contains_priority(temp, 3);
		right = temp->next;
		right->prev = NULL;
		left = temp->prev;
		left->next = NULL;
		return (init_btree(temp, create_tokentree(&left), create_tokentree(&right)));
	}
	return (init_btree(*token, NULL, NULL));
}

/* // goes to the start of the token list
t_token	*get_startlst(t_token *token)
{
	while (token->prev != NULL)
		token = token->prev;
	return (token);
} */