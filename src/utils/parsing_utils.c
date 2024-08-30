/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:53:41 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/30 16:53:41 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c, t_data *data)
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

int is_special(char *input, int *i)
{
	if ((input[*i] == O_PAR) || (input[*i] == O_PAR))
	{
		(*i)++;
		return (1);
	}
	if ((input[*i] == I_REDIR) || (input[*i] == O_REDIR) \
		|| (input[*i] == PIPE) || (input[*i] == '&'))
	{
		if ((input[*i] == I_REDIR) || (input[*i] == O_REDIR) \
		|| (input[*i] == PIPE) || (input[*i] == '&'))
			(*i)++;
		(*i)++;
	}
	return (0);
}
