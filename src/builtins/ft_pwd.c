/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:16:35 by pierre            #+#    #+#             */
/*   Updated: 2024/09/17 12:08:06 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* include "" */
#include "minishell.h"

char	*get_cwd(void)
{
	char	buffer[1000];

	if (!getcwd(buffer, 1000))
	{
		ft_putstr_fd(PWD_ERROR, 2);
		return (NULL);
	}
	return (ft_strdup(buffer));
}

void	ft_pwd(t_token *token, t_data *data, int fd)
{
	char	*path;

	if (token != NULL && token->token_type == WORD)
	{
		error_disp("pwd", "too many arguments");
		data->exit_status = 1;
		return ;
	}
	path = get_cwd();
	if (path)
	{
		ft_putstr_fd(path, fd);
		ft_putstr_fd("\n", fd);
		free(path);
		data->exit_status = 0;
	}
}
