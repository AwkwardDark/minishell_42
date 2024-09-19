/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:32:47 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/19 23:56:51 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// sets the env and export variables OLDPWD and PWD after the cd cmd
static void	setcd_env(t_data *data, char *cwd, char *oldwd)
{
	add_or_replace(&data->env, ft_strdup("OLDPWD"), oldwd);
	add_or_replace(&data->env, ft_strdup("PWD"), cwd);
}

// cahnge directory to $HOME
static void	ft_cdhome(t_data *data)
{
	char	*path;
	char	*wd;

	wd = get_cwd();
	path = get_env(data->env, "HOME");
	if (!path)
	{
		ft_putstr2("minishell: cd: HOME not set\n", 2);
		data->exit_status = 1;
		return ;
	}
	else if (chdir(path) < 0)
	{
		error_disp("cd", strerror(errno));
		data->exit_status = 1;
	}
	else
	{
		data->exit_status = 0;
		setcd_env(data, get_cwd(), wd);
	}
}

// handles the cd builtin
void	ft_cd(t_token *token, t_data *data)
{
	char	*path;
	char	*wd;

	wd = get_cwd();
	if (token == NULL || token->token_type != WORD)
	{
		ft_cdhome(data);
		return ;
	}
	path = token->content;
	if (token->next != NULL && token->next->token_type == WORD)
	{
		error_disp("cd", "too many arguments");
		data->exit_status = 1;
	}
	else if (chdir(path) < 0)
	{
		error_disp("cd", strerror(errno));
		data->exit_status = 1;
	}
	else
	{
		data->exit_status = 0;
		setcd_env(data, get_cwd(), wd);
	}
}
