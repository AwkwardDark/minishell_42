/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:02:44 by pierre            #+#    #+#             */
/*   Updated: 2024/09/17 12:20:26 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// series or single open(s) and redirection(s) from a file to the stdin TODO
void	in_redirection(t_token *token, t_data *data)
{
	int	fd;

	while (token != NULL)
	{
		if (token->token_type == R_IN)
		{
			fd = open(token->redir, O_RDONLY);
			if (fd < 0 || dup2(fd, STDIN_FILENO) < 0)
			{
				clr_gb(data->bin);
				ft_free_exit(data);
				error_disp_exit("", strerror(errno), 1);
			}
			close(fd);
		}
		token = token->next;
	}
}

// series of open and reenvdirections to an OUT FILE
void	out_redirection(t_token *token, t_data *data)
{
	int	fd;

	while (token != NULL)
	{
		if (token->token_type == R_OUT || token->token_type == APPEND)
		{
			if (token->token_type == R_OUT)
				fd = open(token->redir, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			else if (token->token_type == APPEND)
				fd = open(token->redir, O_CREAT | O_WRONLY | O_APPEND, 0664);
			if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
			{
				clr_gb(data->bin);
				ft_free_exit(data);
				error_disp_exit("", strerror(errno), 1);
			}
			close(fd);
		}
		token = token->next;
	}
}

// function that returns the next word useful in case fo redir or hereodocs
static t_token	*ft_getnextword(t_token *token)
{
	if (!token)
	{
		ft_putstr_fd("big problem man\n", 2);
		exit(1);
	}
	while (token->token_type != WORD)
		token = token->next;
	return (token);
}

/* manages children behaviour depending on the flag */
void	redirect_files(t_token *token, int *pipe, int flag, t_data *data)
{
	signal(SIGINT, child_sigint);
	close(pipe[0]);
	in_redirection(token, data);
	if (flag == PIPE)
	{
		if (dup2(pipe[1], STDOUT_FILENO) < 0)
			error_disp_exit("minishell: dup2: ", strerror(errno), 1);
	}
	close(pipe[1]);
	signal(SIGQUIT, SIG_DFL);
	if (ft_is_builtins(token->content))
		exec_subbuiltin(token, data, pipe);
	out_redirection(token, data);
	executer(data, ft_getnextword(token));
}
