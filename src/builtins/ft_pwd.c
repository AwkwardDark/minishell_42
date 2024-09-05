/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 22:16:35 by pierre            #+#    #+#             */
/*   Updated: 2024/08/29 15:09:06 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* include "" */
#include "minishell.h"

void	ft_pwd(void)
{
	char	buffer[1000];

	if (!getcwd(buffer, 1000))
		perror("minishell");
	else
		printf("%s\n", buffer);
}
