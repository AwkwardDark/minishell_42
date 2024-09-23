/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:02:44 by pierre            #+#    #+#             */
/*   Updated: 2024/09/23 16:25:02 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect(t_token *token, t_data *data)
{
	while (token)
	{
		if (token->token_type == R_IN)
			in_redirection(token, data);
		else if (token->token_type == R_OUT || token->token_type == APPEND)
			out_redirection(token, data);
		token = token->next;
	}
}

// series or single open(s) and redirection(s) from a file to the stdin TODO
void	in_redirection(t_token *token, t_data *data)
{
	int	fd;

	if (token->wildcard)
		ft_redir_wildcard(token, &fd);
	if (token->del_wild_flag == 0)
		fd = open(token->redir, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || token->del_wild_flag)
	{
		if (token->del_wild_flag || token->redir[0] == '\0')
			ft_ambiguous_redirect(token);
		else
			error_disp_exit(token->redir, get_error_message(token->redir), -1);
		ft_free_exit(data);
		exit(1);
	}
	close(fd);
}

// series of open and reenvdirections to an OUT FILE
void	out_redirection(t_token *token, t_data *data)
{
	int	fd;

	ft_open_redirout(token, &fd);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || token->del_wild_flag)
	{
		if (token->del_wild_flag || token->redir[0] == '\0')
			ft_ambiguous_redirect(token);
		else
			error_disp_exit(token->redir, get_error_message(token->redir), -1);
		clr_gb(data->bin);
		ft_free_exit(data);
		exit(1);
	}
	close(fd);
}

// function that returns the next word useful in case fo redir or hereodocs
t_token	*ft_getnextword(t_token *token, t_data *data)
{
	if (!token)
	{
		ft_putstr2("big problem man\n", 2);
		exit(1);
	}
	while (token != NULL && token->token_type != WORD)
		token = token->next;
	if (!token)
	{
		clr_gb(data->bin);
		ft_free_exit(data);
		exit(1);
	}
	return (token);
}

/* manages children behaviour depending on the flag */
void	redirect_files(t_token *token, int *pipe, int flag, t_data *data)
{
	signal(SIGINT, child_sigint);
	close(pipe[0]);
	add_fdtogb(data->bin, pipe[1]);
	if (flag == PIPE)
	{
		if (dup2(pipe[1], STDOUT_FILENO) < 0)
		{
			clr_gb(data->bin);
			ft_free_exit(data);
			error_disp_exit("minishell: dup2: ", strerror(errno), 1);
		}
	}
	close(pipe[1]);
	signal(SIGQUIT, SIG_DFL);
	redirect(token, data);
	if (ft_is_builtins(token))
		exec_subbuiltin(ft_getnextword(token, data), data);
	executer(data, ft_getnextword(token, data));
}
