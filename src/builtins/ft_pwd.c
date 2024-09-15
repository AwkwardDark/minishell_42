/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:16:35 by pierre            #+#    #+#             */
/*   Updated: 2024/09/16 00:36:18 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* include "" */
#include "minishell.h"

char	*get_cwd(void)
{
	char	buffer[1000];

	if (!getcwd(buffer, 1000))
	{
		perror("minishell");
		return (NULL);
	}
	return (ft_strdup(buffer));
}

void	ft_pwd(void)
{
	char	*path;

	path = get_cwd();
	if (!path)
	{
		printf("%s\n", path);
		free(path);
	}
}
