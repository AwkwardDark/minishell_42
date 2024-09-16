/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:01:23 by pierre            #+#    #+#             */
/*   Updated: 2024/09/16 18:36:43 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	returns positive value > 1 if there is a redir out to  a file
	return 1 if nothing is found
	and return -1 f there was any error during the open
*/
static int	get_redir(t_token *token)
{
	int	fd;

	fd = 1;
	while (token != NULL)
	{
		if (token->token_type == R_OUT || token->token_type == APPEND)
		{
			if (token->token_type == R_OUT)
				fd = open(token->redir, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			else if (token->token_type == APPEND)
				fd = open(token->redir, O_CREAT | O_WRONLY | O_APPEND, 0664);
			if (fd < 0)
			{
				error_disp(token->redir, strerror(errno));
				fd = -1;
				break ;
			}
		}
		token = token->next;
	}
	return (fd);
}

// exit missing !
void	exec_builtin(t_token *token, t_data *data, int flag)
{
	int	redir;

	if (flag == PIPE)
		return ;
	redir = get_redir(token);
	if (redir < 0)
	{
		data->exit_status = 1;
		return ;
	}
	if (!ft_strcmp(token->content, "echo"))
		ft_echo(token->next, redir, data);
	else if (!ft_strcmp(token->content, "cd"))
		ft_cd(token->next, data);
	else if (!ft_strcmp(token->content, "env"))
		ft_env(data, redir);
	else if (!ft_strcmp(token->content, "pwd"))
		ft_pwd(token->next, data, redir);
	else if (!ft_strcmp(token->content, "unset"))
		ft_unset(token->next, data);
	else if (!ft_strcmp(token->content, "export"))
		ft_export(data, token->next);
	if (redir != 1)
		close(redir);
}
