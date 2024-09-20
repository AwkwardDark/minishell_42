/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:01:23 by pierre            #+#    #+#             */
/*   Updated: 2024/09/20 14:44:46 by pajimene         ###   ########.fr       */
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
			if (token->wildcard)
				ft_redir_wildcard(token);
			if (token->token_type == R_OUT && token->del_wild_flag == 0)
				fd = open(token->redir, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			else if (token->token_type == APPEND && token->del_wild_flag == 0)
				fd = open(token->redir, O_CREAT | O_WRONLY | O_APPEND, 0664);
			if (token->del_wild_flag || token->redir[0] == '\0')
			{
				ft_putstr_fd("minishell: ", 2);
				if (token->redir[0] == '\0')
					ft_putstr_fd(token->old_redir, 2);
				else
					ft_putstr_fd(token->redir, 2);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				return (-1);
			}
			if (fd < 0)
			{
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
		ft_export(data, token->next, redir);
	else
		ft_exit(token->next, data);
	if (redir != 1)
		close(redir);
}
