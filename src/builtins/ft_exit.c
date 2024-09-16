/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:34:32 by pierre            #+#    #+#             */
/*   Updated: 2024/09/16 22:51:31 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_token *token, t_data *data)
{
	int	status;

	if (token == NULL || token->token_type != WORD)
	{
		clr_gb(data->bin);
		ft_free_exit(data);
		exit(0);
	}
	else if (is_number(token->content))
	{
		status = ft_atoi(token->content);
		clr_gb(data->bin);
		ft_free_exit(data);
		exit(status);
	}
	else
	{
		clr_gb(data->bin);
		ft_free_exit(data);
		ft_putstr_fd("minishell: 1 numeric argument expected\n", 2);
		exit(2);
	}
}
