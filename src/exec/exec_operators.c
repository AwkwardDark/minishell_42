/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:51:31 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/09 13:52:08 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_or(t_btree *tree, t_env *env)
{
	int	ret;

	ret = exec_btree(tree->left_child, env);
	if (ret == 0)
		return (0);
	return (exec_btree(tree->right_child, env));
}

int	exec_and(t_btree *tree, t_env *env)
{
	int	ret;

	ret = exec_btree(tree->left_child, env);
	if (ret != 0)
		return (ret);
	ret = exec_btree(tree->right_child, env);
	if (ret != 0)
		return (ret);
	return (0);
}
