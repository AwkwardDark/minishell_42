/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:38:20 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/13 14:38:21 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*checks if the char c is a single or double quote*/
int	ft_is_quote(char c, t_data *data)
{
	if (c == S_QUOTE)
	{
		data->quote_type = S_QUOTE;
		return (1);
	}
	if (c == D_QUOTE)
	{
		data->quote_type = D_QUOTE;
		return (1);
	}
	return (0);
}

/*Checks if the char is a simple or double symbol (operator)*/
static int	ft_is_symbol_lexer(char c, t_data *data)
{
	if (c == O_PAREN)
		return (1);
	if (c == C_PAREN)
		return (1);
	if (c == P)
	{
		data->symbol = P;
		return (1);
	}
	if (c == I_R)
	{
		data->symbol = I_R;
		return (1);
	}
	if (c == O_R)
	{
		data->symbol = O_R;
		return (1);
	}
	return (0);
}

int	ft_is_operator(char *input, int *i, t_data *data)
{	
	if ((input[*i] == O_PAREN) || (input[*i] == C_PAREN))
		return ((*i)++, 1);
	if (ft_is_symbol_lexer(input[*i], data))
	{
		if (input[*i + 1])
		{
			if (input[*i + 1] == data->symbol)
				(*i)++;
		}
		return ((*i)++, 1);
	}
	if (input[*i] == '&')
	{
		(*i) += 2;
		return (1);
	}
	if (input[*i + 1])
	{
		if (ft_is_symbol_lexer(input[*i + 1], data))
			return ((*i)++, 1);
		if (input[*i + 1] == '&')
			return ((*i)++, 1);
	}
	return (0);
}
