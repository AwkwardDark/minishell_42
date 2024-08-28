/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 15:25:37 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_exit(t_data *data)
{
	if (data->env)
		clear_wordar(data->env);
}

int	ft_error_clean(t_data *data, int code)
{
	(void)data;
	if (code == 1)
		ft_putstr_fd("Malloc error\n", 2);
	return (1);
}
