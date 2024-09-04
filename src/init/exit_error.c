/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:08:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/04 18:59:04 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Before exiting the program, it free the environment list, the prompt input,
the token parsing list and the rest of malloc'd structs*/
void	ft_free_exit(t_data *data)
{
	if (data->env)
		ft_clrenv(&data->env);
	if (data->input)
		free(data->input);
	if (data->token_lst)
		ft_free_lst(&data->token_lst);
	if (data)
		free(data);
	rl_clear_history();
}

/*It writes on the STDERR an error message*/
void	ft_error(int code)
{
	if (code == 0)
		ft_putstr_fd("minishell: quote syntax error\n", 2);
	if (code == 1)
		ft_putstr_fd("minishell: and (&&) logical operator syntax error\n", 2);
	if (code == 2)
		ft_putstr_fd("minishell: or (||) logical operator syntax error\n", 2);
	if (code == 3)
		ft_putstr_fd("minishell: heredoc (<<) syntax error\n", 2);
	if (code == 4)
		ft_putstr_fd("minishell: append (>>) syntax error\n", 2);
	if (code == 5)
		ft_putstr_fd("minishell: parenthesis syntax error\n", 2);
	if (code == 6)
		ft_putstr_fd("minishell: env list creation eroor\n", 2);
	if (code == 7)
		ft_putstr_fd("minishell: malloc error\n", 2);
}
