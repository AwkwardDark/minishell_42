/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:02:44 by pierre            #+#    #+#             */
/*   Updated: 2024/09/05 00:02:09 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// series or single open(s) and redirection(s) from a file to the stdin TODO
void	in_redirection(t_token *token)
{
	int	fd;

	while (token != NULL)
	{
		if (token->token_type == R_IN)
		{
			fd = open(token->content, O_RDONLY);
			if (fd < 0)
				error_disp_exit(token->content, ": open error", 1);
			if (dup2(fd, STDIN_FILENO) < 0)
				error_disp_exit("minishell: dup2: ", strerror(errno), 1);
			close(fd);
		}
		token = token->next;
	}
}

// series of open and redirections to an OUT FILE
void	out_redirection(t_token *token)
{
	int	fd;

	while (token != NULL)
	{
		if (token->token_type == R_OUT || token->token_type == APPEND)
		{
			if (token->token_type == R_OUT)
				fd = open(token->content, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			else if (token->token_type == APPEND)
				fd = open(token->content, O_CREAT | O_WRONLY | O_APPEND, 0664);
			if (fd < 0)
				error_disp_exit(token->content, ": open error", 1);
			if (dup2(fd, STDIN_FILENO) < 0)
				error_disp_exit("minishell: dup2: ", strerror(errno), 1);
			close(fd);
		}
		token = token->next;
	}
}

/* manages children behaviour depending on the flag */
void	redirect_files(t_token *token, int *pipe, int flag, t_env *env)
{
	if (flag == PIPE)
		close(pipe[0]);
	in_redirection(token);
	if (flag == PIPE)
	{
		if (dup2(pipe[1], STDOUT_FILENO) < 0)
			error_disp_exit("minishell: dup2: ", strerror(errno), 1);
		close(pipe[1]);
	}
	out_redirection(token);
	executer(env, token);
}
