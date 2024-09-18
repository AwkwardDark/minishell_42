/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:13 by pierre            #+#    #+#             */
/*   Updated: 2024/09/18 23:40:01 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec(t_token *token, t_data *data, int flag)
{
	int	child;
	int	fd[2];

	if (pipe(fd) < 0)
		error_disp_exit("minishell: pipe: ", strerror(errno), 1);
	child = fork();
	if (child < 0)
		error_disp_exit("minishell: fork: ", strerror(errno), 1);
	if (child == 0)
		redirect_files(token, fd, flag, data);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		error_disp_exit("minishell: dup2: ", strerror(errno), 1);
	close(fd[0]);
	return (child);
}

static int	parse_exec(t_btree *tree, t_data *data, int flag)
{
	ft_expand(tree->token, data);
	ft_wildcard(&tree->token, tree);
	if (flag != PIPE && ft_is_builtins(tree->token->content))
	{
		exec_builtin(tree->token, data);
		return (-1);
	}
	if (is_heredoc(tree->token))
		do_mydoc(tree->token, data);
	if (data->exit_status == 0)
		return (exec(tree->token, data, flag));
	return (-1);
}

/*
	general function of exewcution of the pipes
*/
static void	exec_pipes(t_btree *tree, t_data *data, int last_command)
{
	if (is_leaf(tree))
		parse_exec(tree, data, PIPE);
	else if (last_command)
	{
		exec_pipes(tree->left_child, data, 0);
		if (ft_is_builtins(tree->right_child->token->content))
			wait_children(parse_exec(tree->right_child, data, PIPE), data);
		else
			wait_children(parse_exec(tree->right_child, data, SIMPLE_COMMAND),
				data);
	}
	else
	{
		exec_pipes(tree->left_child, data, 0);
		exec_pipes(tree->right_child, data, 0);
	}
}

/* 	General function of execution TODO: ADJUSTEMENT ON THE FI LE*/
/* 	DESCRIPTOR FOR THE HEREDOC SAME PROBLEM AS FOR THE PIPES. */
// ror_disp_exit("minishell: exec: ", strerror(errno), 126);
void	exec_btree_aux(t_btree *tree, t_data *data)
{
	if (is_leaf(tree))
		simplecmd_wait(parse_exec(tree, data, SIMPLE_COMMAND), data);
	else if (tree->token->token_type == PIPE)
		exec_pipes(tree, data, 1);
	else if (tree->token->token_type == OR)
		exec_or(tree, data);
	else if (tree->token->token_type == AND)
		exec_and(tree, data);
}

void	exec_btree(t_btree *tree, t_data *data)
{
	int	infd;

	infd = dup(0);
	add_fdtogb(data->bin, infd);
	signal(SIGINT, parenthandler);
	signal(SIGQUIT, main_sigquit);
	exec_btree_aux(tree, data);
	dup2(infd, STDIN_FILENO);
	close_fds(data->bin);
	g_signal = 0;
}
