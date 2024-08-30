/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/30 15:02:42 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_exit(t_data *data)
{
	if (data->env)
		clear_wordar(data->env);
	if (data->input)
		free(data->input);
	if (data->token_lst)
		ft_free_lst(data->token_lst);
	rl_clear_history();
}

void	ft_error(int code)
{
	if (code == 0)
		ft_putstr_fd("Quote syntax error\n", 2);
	if (code == 1)
		ft_putstr_fd("Operator syntax error\n", 2);
	if (code == 2)
		ft_putstr_fd("Malloc error\n", 2);
}
