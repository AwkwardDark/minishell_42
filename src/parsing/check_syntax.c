/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:04:29 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 16:23:25 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int ft_quote_syntax(char *input)
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

/*It checks basic non-contextual syntax. It checks for non closed single 
or double quotes, and the same for brackets*/
int	ft_check_syntax(char *input)
{
	if (ft_quote_syntax(input) == 1)
		return(ft_error(0), 1);
	//if (ft_bracket_syntax(cmd) == 1)
	//	printf(SYNTAX_ERR_B);
	return (0);
}
