/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 16:26:05 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_exit(t_data *data)
{
	if (data->env)
		clear_wordar(data->env);
	if (data->input)
		free(data->input);
}

void	ft_error(int code)
{
	if (code == 0)
		ft_putstr_fd("Quote Syntax error\n", 2);
	if (code == 2)
		ft_putstr_fd("Malloc error\n", 2);
}
