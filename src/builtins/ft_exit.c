/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:34:32 by pierre            #+#    #+#             */
/*   Updated: 2024/09/17 18:51:51 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_end(int exno, t_data *data)
{
	clr_gb(data->bin);
	ft_free_exit(data);
	exit(exno);
}

static int	parse_exnum(char *cmd)
{
	if (!cmd)
		return (0);
	while (*cmd == ' ')
		cmd++;
	if (*cmd == '-')
		cmd++;
	while (ft_isdigit(*cmd))
		cmd++;
	while (*cmd == ' ')
		cmd++;
	if (*cmd != '\0')
		retrun (0);
	return (1);
}

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
	if (token == NULL || token->token_type != WORD)
		free_end(data, 0);
	else if (token->next != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		free_end(2, data);
	}
}

void	ft_exit_aux(t_token *token, t_data *data)
{
	if (!parse_exnum(token->content))
		
	else
	{
		clr_gb(data->bin);
		ft_free_exit(data);
		ft_putstr_fd("minishell: 1 numeric argument required\n", 2);
		exit(2);
	}
}