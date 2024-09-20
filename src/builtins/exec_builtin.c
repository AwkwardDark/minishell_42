/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:01:23 by pierre            #+#    #+#             */
/*   Updated: 2024/09/20 17:24:07 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_redirin(t_token *token)
{
	int	fd;

	fd = 1;
	while (token != NULL)
	{
		if (token->token_type == R_IN)
		{
			if (token->wildcard)
				ft_redir_wildcard(token, &fd);
			if (token->del_wild_flag == 0)
				fd = open(token->redir, O_RDONLY);
			if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || token->del_wild_flag)
			{
				if (token->del_wild_flag || token->redir[0] == '\0')
					ft_ambiguous_redirect(token);
				else
					error_disp(token->redir, strerror(errno));
				return (-1);
			}
			close(fd);
		}
		token = token->next;
	}
	return (1);
}

/*
	returns positive value > 1 if there is a redir out to  a file
	return 1 if nothing is found
	and return -1 f there was any error during the open
*/
static int	get_redirout(t_token *token)
{
	int	fd;

	fd = 1;
	if (get_redirin(token) < 0)
		return (-1);
	while (token != NULL)
	{
		if (token->token_type == R_OUT || token->token_type == APPEND)
		{
			ft_open_redirout(token, &fd);
			if (fd < 0 || token->del_wild_flag)
			{
				if (token->del_wild_flag || token->redir[0] == '\0')
					ft_ambiguous_redirect(token);
				else
					error_disp(token->redir, strerror(errno));
				return (-1);
			}
		}
		token = token->next;
	}
	return (fd);
}

// execution of a builtin in a subprocess in case of pipe cmds
void	exec_subbuiltin(t_token *token, t_data *data)
{
	int	status;

	if (!ft_strcmp(token->content, "exit"))
		ft_exit(token->next, data);
	else
		exec_builtin(token, data);
	status = data->exit_status;
	clr_gb(data->bin);
	ft_free_exit(data);
	exit(status);
}

// open files, and executes the builtins
void	exec_builtin(t_token *token, t_data *data)
{
	int	redir;

	redir = get_redirout(token);
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
		ft_export(data, token->next, redir);
	else
		ft_exit(token->next, data);
	if (redir != 1)
		close(redir);
}
