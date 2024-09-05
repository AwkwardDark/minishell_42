/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:04:29 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/05 11:25:53 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It checks that all the quotes are correctly closed*/
int	ft_quote_syntax(char *input)
{
	int	i;
	int	count;
	int	flag;

	i = -1;
	count = 1;
	flag = 0;
	while (input[++i])
	{
		if ((input[i] == S_QUOTE) && (flag == 0 || flag == 1))
		{
			flag = 1;
			count *= -1;
		}
		if ((input[i] == D_QUOTE) && (flag == 0 || flag == 2))
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

/*It advances in the input when it's inside some quote*/
static void	ft_check_quote(char *input, int *i, t_data *data)
{
	if (input[*i])
	{
		if (input[*i] == S_QUOTE || input[*i] == D_QUOTE)
		{
			data->quote_type = input[*i];
			(*i)++;
			while (input[*i] != data->quote_type)
				(*i)++;
		}
	}
}

/*It makes sure that logical and redirection operators are well typed,
& or &&& or >>> or ||| is a syntax error for example*/
int	ft_operator_syntax(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		ft_check_quote(input, &i, data);
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

/*It makes sure all the parenthesis are well used, ) or ( isolated are a
syntax error*/
int	ft_parenthesis_syntax(char *input, t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		ft_check_quote(input, &i, data);
		if (input[i] && input[i] == O_PAREN)
		{
			count++;
			i++;
		}
		if (input[i] && input[i] == C_PAREN)
		{
			count--;
			i++;
		}
		if (input[i] && input[i] != O_PAREN && input[i] != C_PAREN)
			i++;
		if (count < 0)
			break ;
	}
	return (count != 0);
}
