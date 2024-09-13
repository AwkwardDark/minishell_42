/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:06:08 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/13 17:36:36 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "" */

#include "minishell.h"

// displays envirement variables if they exist

void	ft_env(t_env *env, t_data *data)
{
	if (!env)
		return ;
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	data->exit_status = 0;
}
