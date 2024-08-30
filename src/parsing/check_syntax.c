/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:04:29 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/30 16:04:11 by pajimene         ###   ########.fr       */
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
