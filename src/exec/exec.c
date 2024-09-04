/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:13 by pierre            #+#    #+#             */
/*   Updated: 2024/09/04 10:21:26 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	general function of execution
*/
int	exec_btree(t_btree *tree)
{
	if (is_leaf(tree))
		return (1);
	else if (tree->token->token_type == PIPE)
		exec_pipes(tree, 1);
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

/* 
	general function of exewcution of the pipes
*/
int	exec_pipes(t_btree *tree, int last_command)
{
	if (is_leaf(tree))
		redirect_io();
	if (tree->token->token_type == PIPE)
	{
		exec_pipes(tree->left_child, 0);
		return (wait_last());
	}
	else
	{
		exec_pipes(tree->left_child, 0);
		//
		exec_pipes(tree->right_child, 0);
	}
}


int	parse_exec(t_env env, t_token *token, int flag)
{
	int	fd[2];
	int	ret;

	if (flag == PIPE && pipe(fd) < 0)
		error_disp_exit("minishell: pipe: ", "", strerror(errno), 1);
	ret = fork();
	if (ret = 0)
		// do the excution with the param given
	if (flag == PIPE)
		close(fd[1]);
	if (flag == PIPE && dup2(fd[0], STDIN_FILENO) < 0)
		error_disp_exit("minishell: dup2: ", "", strerror(errno), 1);
	// no wait here !!
}

/* creates (pipe, children and redirects) */
int	redirect_io(t_env env, t_token *token, int flag)
{
	int	fd[2];
	int	child;

	if (pipe(fd) < 0)
		error_disp_exit("pipex: pipe: ", "", strerror(errno), 1);
	child = fork();
	if (child < 0)
		error_disp_exit("pipex: fork: ", "", strerror(errno), 1);
	else if (child == 0)
		redirect_files(cmd, data, fd, flag);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		error_disp_exit("pipex: dup2: ", "", strerror(errno), 1);
	close(fd[0]);
	return (child); 
}

int	waitlst_child(int pid)
{

}