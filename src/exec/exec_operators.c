/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:51:31 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/16 17:54:39 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_or(t_btree *tree, t_data *data)
{

	exec_btree(tree->left_child, data);
	if (data->exit_status == 0)
		return ;
	exec_btree(tree->right_child, data);
}

void	exec_and(t_btree *tree, t_data *data)
{
	exec_btree(tree->left_child, data);
	if (data->exit_status != 0)
		return ;
	exec_btree(tree->right_child, data);
}
