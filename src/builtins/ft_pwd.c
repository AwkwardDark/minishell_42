/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:16:35 by pierre            #+#    #+#             */
/*   Updated: 2024/09/20 00:03:22 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* include "" */
#include "minishell.h"

// retreives the pwd
char	*get_cwd(void)
{
	char	buffer[1000];

	if (!getcwd(buffer, 1000))
	{
		ft_putstr2(PWD_ERROR, 2);
		return (NULL);
	}
	return (ft_strdup(buffer));
}

// prints working directory
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
		ft_putstr2(path, fd);
		ft_putstr2("\n", fd);
		free(path);
		data->exit_status = 0;
	}
}
