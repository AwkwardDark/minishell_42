/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:06:08 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/20 09:34:53 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "" */

#include "minishell.h"

// displays envirement variables if they exist
void	ft_env(t_data *data, int fd)
{
	t_env	*env;

	env = data->env;
	if (!env)
		return ;
	while (env != NULL)
	{
		if (ft_putstr2(env->key, fd) < 0)
		{
			data->exit_status = 1;
			return ;
		}
		ft_putstr2("=", fd);
		ft_putstr2(env->value, fd);
		ft_putstr2("\n", fd);
		env = env->next;
	}
	data->exit_status = 0;
}
