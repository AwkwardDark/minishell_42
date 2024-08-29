/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:06:08 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/29 12:02:56 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "" */

#include "builtin.h"

// displays envirement variables if they exist

void	ft_env(t_env *env)
{
	if (!env)
		return ;
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
