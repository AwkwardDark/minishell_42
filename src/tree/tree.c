/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:21:21 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/20 15:17:19 by pajimene         ###   ########.fr       */
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
	clr_btree(tree->left_child);
	clr_btree(tree->right_child);
	ft_free_lst(&tree->token);
	free(tree);
}

/*
	TODO
	check for other free to do for char * content
*/
t_token	*remove_parenthesis(t_token *token)
{
	t_token	*temp;
	t_token	*end;

	temp = token;
	if (token->token_type != C_PAR || get_startlst(token)->token_type != O_PAR)
		return (token);
	if (ignore_parenthesis(token)->prev->prev != NULL || token->next != NULL)
		return (token);
	end = ignore_parenthesis(token);
	if (end->prev->token_type == O_PAR)
	{
		ft_free_onetoken(end->prev);
		end->prev = NULL;
		temp = temp->prev;
		ft_free_onetoken(temp->next);
		temp->next = NULL;
		return (temp);
	}
	return (token);
}

// goes to the start of the token list
t_token	*get_startlst(t_token *token)
{
	while (token->prev != NULL)
		token = token->prev;
	return (token);
}

/*
	ceates the token tree handles priority
	and , or and pipes 
*/
t_btree	*create_tokentree(t_token **token)
{
	t_token	*temp;
	t_token	*temp2;
	t_token	*right;
	t_token	*left;

	if (!token)
		return (NULL);
	temp = ft_lstlast(*token);
	temp = remove_parenthesis(temp);
	if (contains_priority(temp, 3) || contains_priority(temp, 2))
	{
		temp2 = contains_priority(temp, 3);
		if (!temp2)
			temp2 = contains_priority(temp, 2);
		right = temp2->next;
		left = temp2->prev;
		right->prev = NULL;
		left->next = NULL;
		temp2->next = NULL;
		temp2->prev = NULL;
		return (init_btree(temp2, create_tokentree(&left),
				create_tokentree(&right)));
	}
	return (init_btree(get_startlst(temp), NULL, NULL));
}
