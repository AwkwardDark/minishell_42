/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:06:08 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/17 12:08:06 by pajimene         ###   ########.fr       */
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
		ft_putstr_fd(env->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(env->value, fd);
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
	data->exit_status = 0;
}
