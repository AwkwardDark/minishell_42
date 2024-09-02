/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/02 18:19:02 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exit(t_data *data)
{
	if (data->env)
	 	ft_clrenv(&data->env);
	if (data->input)
		free(data->input);
	if (data->token_lst)
		ft_free_lst(&data->token_lst);
	rl_clear_history();
}

void	ft_error(int code)
{
	if (code == 0)
		ft_putstr_fd("Quote syntax error\n", 2);
	if (code == 1)
		ft_putstr_fd("And (&&) logical operator syntax error\n", 2);
	if (code == 2)
		ft_putstr_fd("Or (||) logical operator syntax error\n", 2);
	if (code == 3)
		ft_putstr_fd("Heredoc (<<) syntax error\n", 2);
	if (code == 4)
		ft_putstr_fd("Append (>>) syntax error\n", 2);
	if (code == 5)
		ft_putstr_fd("Parenthesis syntax error\n", 2);
	if (code == 6)
		ft_putstr_fd("Malloc error\n", 2);
}
