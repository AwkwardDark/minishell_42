/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:41:15 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/19 12:02:43 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pre_exp_len(char *line, int i)
{
	int	len;

	len = 0;
	while (line[i] && !ft_is_symbol(line[i]))
	{
		len++;
		i++;
	}
	return (len);
}

char *ft_heredoc_expansion(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == DOLLAR)
		{
			
		}
	}
}
