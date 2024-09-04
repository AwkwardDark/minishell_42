/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:13 by pierre            #+#    #+#             */
/*   Updated: 2024/09/04 17:11:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_exec(t_token *token, t_env *env, int flag)
{
	int fd[2];
	int	child;

	if (is_heredoc(token))
		do_mydoc(token, get_limiter(token));
	if (flag == PIPE)
	{
		if (pipe(fd) < 0)
			fprintf(stderr, "error\n");
	}
	child = fork();
	if (child == 0)
		redirect_files(token, fd, flag, env);
	if (flag == PIPE)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			fprintf(stderr, "error\n");
		close(fd[0]);
	}
	return (child);
}

/* 
	general function of exewcution of the pipes
*/
static int	exec_pipes(t_btree *tree, t_env *env, int last_command)
{
	if (is_leaf(tree))
		return (parse_exec(tree->token, env, PIPE));
	else if (last_command)
	{
		exec_pipes(tree->left_child, env, 0);
		return (wait_children(parse_exec(tree->right_child->token, env, SIMPLE_COMMAND)));
	}
	else
	{
		exec_pipes(tree->left_child, env, 0);
		exec_pipes(tree->right_child, env, 0);
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

/* 
	general function of execution
*/
int	exec_btree(t_btree *tree, t_env *env)
{
	if (is_leaf(tree))
		parse_exec(tree->token, env, SIMPLE_COMMAND);
	else if (tree->token->token_type == PIPE)
		return (exec_pipes(tree, env,  1));
	else if (tree->token->token_type == OR)
		return (exec_btree(tree->left_child, env) || exec_btree(tree->right_child, env));
	else if (tree->token->token_type == AND)
	{
		if (!exec_btree(tree->left_child, env))
			return (0);
		if (!exec_btree(tree->right_child, env))
			return (0);
		return (1);
	}
}

