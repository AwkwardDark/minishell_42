/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:51:31 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/20 00:05:16 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// executes the second command if the first failed
void	exec_or(t_btree *tree, t_data *data)
{
	exec_btree_aux(tree->left_child, data);
	if (data->exit_status == 0)
		return ;
	exec_btree_aux(tree->right_child, data);
}

// executes the second command if the first succeeded
void	exec_and(t_btree *tree, t_data *data)
{
	exec_btree_aux(tree->left_child, data);
	if (data->exit_status != 0)
		return ;
	exec_btree_aux(tree->right_child, data);
}
