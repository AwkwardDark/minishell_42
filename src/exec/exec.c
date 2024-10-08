/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:13 by pierre            #+#    #+#             */
/*   Updated: 2024/09/22 20:19:02 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handles pipes, dup2 and fork
static int	exec(t_token *token, t_data *data, int flag)
{
	int	child;
	int	fd[2];

	if (pipe(fd) < 0)
		return (free_exec_pipe(data));
	add_fdtogb(data->bin, fd[0]);
	add_fdtogb(data->bin, fd[1]);
	child = fork();
	if (child < 0)
		return (free_exec_fork(data));
	if (child == 0)
		redirect_files(token, fd, flag, data);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		free_exec_dup2(data);
	close(fd[0]);
	return (child);
}

// handles expands, does the wildcards, heredoc
static int	parse_exec(t_btree *tree, t_data *data, int flag)
{
	ft_expand(tree->token, data);
	ft_wildcard(&tree->token, tree);
	if (is_heredoc(tree->token))
		do_mydoc(tree->token, data);
	if (data->exit_status >= 128)
		return (-1);
	return (exec(tree->token, data, flag));
}

// special recursive function for the PIPES cmds
static void	exec_pipes(t_btree *tree, t_data *data, int last_command)
{
	if (is_leaf(tree))
		parse_exec(tree, data, PIPE);
	else if (last_command)
	{
		exec_pipes(tree->left_child, data, 0);
		wait_children(parse_exec(tree->right_child, data, SIMPLE_COMMAND),
			data);
	}
	else
	{
		exec_pipes(tree->left_child, data, 0);
		exec_pipes(tree->right_child, data, 0);
	}
}

// recursive function to execute the tree commands
void	exec_btree_aux(t_btree *tree, t_data *data)
{
	if (is_leaf(tree))
	{
		if (is_heredoc(tree->token))
			simplecmd_wait(parse_exec(tree, data, SIMPLE_COMMAND), data);
		else if (ft_is_builtins(tree->token))
		{
			ft_expand(tree->token, data);
			ft_wildcard(&tree->token, tree);
			exec_builtin(ft_getnextword(tree->token, data), data,
				get_redirbuiltin(tree->token));
			simplecmd_wait(-1, data);
		}
		else
			simplecmd_wait(parse_exec(tree, data, SIMPLE_COMMAND), data);
	}
	else if (tree->token->token_type == PIPE)
		exec_pipes(tree, data, 1);
	else if (tree->token->token_type == OR)
		exec_or(tree, data);
	else if (tree->token->token_type == AND)
		exec_and(tree, data);
}

// main binary tree execution
void	exec_btree(t_btree *tree, t_data *data)
{
	data->infd = dup(0);
	add_fdtogb(data->bin, data->infd);
	signal(SIGINT, parenthandler);
	signal(SIGQUIT, main_sigquit);
	exec_btree_aux(tree, data);
	dup2(data->infd, STDIN_FILENO);
	close_fds(data->bin);
	g_signal = 0;
}
