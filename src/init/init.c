/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:35:25 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/30 16:13:47 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_data(char **envp, t_data *data)
{
	
	if (!envp || !envp[0])
		data->env = NULL;
	else
	{
		data->env = ft_copy_env(envp);
		if (!data->env)
			return (ft_error(2), 1);
	}
	data->exit_status = 0;
	return (0);
}
