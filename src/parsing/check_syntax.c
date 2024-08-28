/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:04:29 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 12:19:03 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*It checks basic non-contextual syntax. It checks for non closed single 
or double quotes, and the same for brackets*/
void	ft_check_syntax(t_cmd *cmd)
{
	if (ft_quote_syntax(cmd) == 1)
		printf(SYNTAX_ERR_Q);
	//if (ft_bracket_syntax(cmd) == 1)
	//	printf(SYNTAX_ERR_B);
}


int ft_quote_syntax(t_cmd *cmd)
{
	int		i;
	int		count;
	char	*buffer;

	i = -1;
	count = 1;
	buffer = cmd->buffer;
	while (buffer[++i])
	{
		if ((buffer[i] == '\'') && (cmd->flag == 0 || cmd->flag == 1))
		{
			cmd->flag = 1;
			count *= -1;
		}
		if ((buffer[i] == '"') && (cmd->flag == 0|| cmd->flag == 2))
		{
			cmd->flag = 2;
			count *= -1;
		}
		if (count == 1)
			cmd->flag = 0;
	}
	if (count == -1)
		return (1);
	return (0);
}
