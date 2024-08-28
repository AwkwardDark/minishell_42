/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:16:35 by pierre            #+#    #+#             */
/*   Updated: 2024/08/27 23:51:54 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* include "" */
#include "builtin.h"

void	ft_pwd(void)
{
	char	buffer[1000];

	if (!getcwd(buffer, 1000))
		perror("minishell");
	else
		printf("%s\n", buffer);
}
