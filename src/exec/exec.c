/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:13 by pierre            #+#    #+#             */
/*   Updated: 2024/09/12 11:19:29 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_exec(t_token *token, t_env *env, int flag)
{
	int	fd[2];
	int	child;

	ft_expand(token, env);
	ft_print_lst(token);
	ft_wildcard(&token);
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
	int	re;

	if (is_leaf(tree))
		return (parse_exec(tree->token, env, PIPE));
	else if (last_command)
	{
		exec_pipes(tree->left_child, env, 0);
		re = wait_children(parse_exec(tree->right_child->token,
					env, SIMPLE_COMMAND));
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

/* 
	General function of execution TODO: ADJUSTEMENT ON THE FILE 
	DESCRIPTOR FOR THE HEREDOC SAME PROBLEM AS FOR THE PIPES.

	norm it also
*/
static int	exec_btree_aux(t_btree *tree, t_env *env)
{
	if (is_leaf(tree))
		return (simplecmd_wait(parse_exec(tree->token, env, SIMPLE_COMMAND)));
	else if (tree->token->token_type == PIPE)
		return (exec_pipes(tree, env, 1));
	else if (tree->token->token_type == OR)
		return (exec_or(tree, env));
	else if (tree->token->token_type == AND)
		return (exec_and(tree, env));
	return (-1);
}

int	exec_btree(t_btree *tree, t_env *env)
{
	int	infd;
	int ret;

	infd = dup(0);
	ret = exec_btree_aux(tree, env);
	dup2(infd, STDIN_FILENO);
	close(infd);
	return (ret);
}