/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:30:13 by pierre            #+#    #+#             */
/*   Updated: 2024/09/11 17:50:15 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	exec(t_token *token, t_data *data, int flag)
{
	int	child;
	int fd[2];

	if (flag == PIPE)
	{
		if (pipe(fd) < 0)
			error_disp_exit("minishell: pipe: ", strerror(errno), 1);
	}
	child = fork();
	if (child < 0)
		error_disp_exit("minishell: fork: ", strerror(errno), 1);
	if (child == 0)
		redirect_files(token, fd, flag, data);
	if (flag == PIPE)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			error_disp_exit("minishell: dup2: ", strerror(errno), 1);
		close(fd[0]);
	}
	return (child);
}

static int	parse_exec(t_token *token, t_data *data, int flag)
{
	int	fd[2];
	int	child;

	child = 0;
	if (is_heredoc(token))
		do_mydoc(get_limiter(token), data);
	if (g_signal == 0)
		return (exec(token, data, flag));
	return (-1);
}

/* 
	general function of exewcution of the pipes
*/
static void	exec_pipes(t_btree *tree, t_data *data, int last_command)
{
	if (is_leaf(tree))
		parse_exec(tree->token, data, PIPE);
	else if (last_command)
	{
		exec_pipes(tree->left_child, data, 0);
		wait_children(parse_exec(tree->right_child->token, 
				data, SIMPLE_COMMAND), data);
	}
	else
	{
		exec_pipes(tree->left_child, data, 0);
		exec_pipes(tree->right_child, data, 0);
	}
}

/* 
	General function of execution TODO: ADJUSTEMENT ON THE FILE 
	DESCRIPTOR FOR THE HEREDOC SAME PROBLEM AS FOR THE PIPES.

	norm it also
*/
static void	exec_btree_aux(t_btree *tree, t_data *data)
{
	if (is_leaf(tree))
		simplecmd_wait(parse_exec(tree->token, data, SIMPLE_COMMAND), data);
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

	signal(SIGINT, parenthandler);
	infd = dup(0);
	exec_btree_aux(tree, data);
	dup2(infd, STDIN_FILENO);
	close(infd);
}
