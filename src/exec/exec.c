/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:13 by pierre            #+#    #+#             */
/*   Updated: 2024/09/03 14:43:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_btree(t_btree *tree)
{
	if (is_leaf(tree))
		
	else if (tree->token->token_type == PIPE)
	{
		//redirect ... TODO
		exec_tree(tree->left_child);
		exec_tree(tree->right_child);
	}
	else if (tree->token == OR)
		return (exec_btree(tree->left_child) || exec_btree(tree->right_child));
	else if (tree->token == AND)
	{
		if (!exec_btree(tree->left_child))
			return (0);
		if (!exec_btree(tree->right_child))
			return (0);
		return (1);
	}
}
