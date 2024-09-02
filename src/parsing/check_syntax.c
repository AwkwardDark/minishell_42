/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:04:29 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/02 18:22:36 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_quote_syntax(char *input)
{
	int		i;
	int		count;
	int		flag;

	i = -1;
	count = 1;
	while (input[++i])
	{
		if ((input[i] == '\'') && (flag == 0 || flag == 1))
		{
			flag = 1;
			count *= -1;
		}
		if ((input[i] == '"') && (flag == 0|| flag == 2))
		{
			flag = 2;
			count *= -1;
		}
		if (count == 1)
			flag = 0;
	}
	if (count == -1)
		return (1);
	return (0);
}

int	ft_operator_syntax(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '&')
		{
			i++;
			if (input[i] != '&' || input[i + 1] == '&')
				return (ft_error(1), 1);
		}
		if ((input[i] == P) && (input[i + 1] == P) && (input[i + 2] == P))
			return (ft_error(2), 1);
		if ((input[i] == I_R) && (input[i + 1] == I_R) && (input[i + 2] == I_R))
			return (ft_error(3), 1);
		if ((input[i] == O_R) && (input[i + 1] == O_R) && (input[i + 2] == O_R))
			return (ft_error(4), 1);
		i++;
	}
	return (0);
}

// int	ft_parenthesis_syntax(char *input)
// {
// 	int	i;
// 	int	flag;
	
// 	i = 0;
// 	flag = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == O_PAREN)
// 			flag = 1;
// 		if ()
// 	}
// 	return (0);
// }
