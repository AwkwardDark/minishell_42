/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:13 by pierre            #+#    #+#             */
/*   Updated: 2024/09/06 15:16:16 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_exec(t_token *token, t_env *env, int flag)
{
	int	fd[2];
	int	child;

	if (is_heredoc(token))
		do_mydoc(get_limiter(token));
	if (flag == PIPE)
	{
		if (pipe(fd) < 0)
			error_disp_exit("minishell: pipe: ", strerror(errno), 1);
	}
	child = fork();
	if (child < 0)
		error_disp_exit("minishell: fork: ", strerror(errno), 1);
	if (child == 0)
		redirect_files(token, fd, flag, env);
	if (flag == PIPE)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			error_disp_exit("minishell: dup2: ", strerror(errno), 1);
		close(fd[0]);
	}
	return (child);
}

/* 
	general function of exewcution of the pipes
*/
static int	exec_pipes(t_btree *tree, t_env *env, int last_command)
{
	int	in;
	int	re;

	if (is_leaf(tree))
		return (parse_exec(tree->token, env, PIPE));
	else if (last_command)
	{
		in = dup(0);
		exec_pipes(tree->left_child, env, 0);
		re = wait_children(parse_exec(tree->right_child->token,
					env, SIMPLE_COMMAND));
		dup2(in, STDIN_FILENO);
		close(in);
		return (re);
	}
	else
	{
		exec_pipes(tree->left_child, env, 0);
		exec_pipes(tree->right_child, env, 0);
		return (1);
	}
}

/* waits for all children */
int	wait_children(pid_t last_child)
{
	int	status;
	int	retcode;

	while (ECHILD != errno)
	{
		if (waitpid(0, &status, 0) == last_child)
		{
			if (WIFEXITED(status))
				retcode = WEXITSTATUS(status);
			else
				retcode = WSTOPSIG(status);
		}
	}
	return (retcode);
}

// waits for one process SIMPLE_COMMAND
static int	simplecmd_wait(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

//	general function of execution
int	exec_btree(t_btree *tree, t_env *env)
{
	int	ret;

	if (is_leaf(tree))
		return (simplecmd_wait(parse_exec(tree->token, env, SIMPLE_COMMAND)));
	else if (tree->token->token_type == PIPE)
	{
		return (exec_pipes(tree, env, 1));
	}
	else if (tree->token->token_type == OR)
	{
		exec_btree(tree->left_child, env);
		return (exec_btree(tree->right_child, env));
	}
	else if (tree->token->token_type == AND)
	{
		ret = exec_btree(tree->left_child, env);
		if (ret != 0)
			return (ret);
		ret = exec_btree(tree->right_child, env);
		if (ret != 0)
			return (ret);
		return (0);
	}
	return (-1);
}
