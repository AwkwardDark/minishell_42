/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:06:08 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/28 18:00:56 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "" */

#include "builtin.h"

// displays envirement variables if they exist

void	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		ft_putstr_fd("no envirement variable set\n", 2);
	else
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	printf("LEN: %d\n", i);
}
