/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:49:48 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 16:26:55 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

void	ft_parser(char *input, t_data *data)
{	
	(void)data;
	if (ft_check_syntax(input))
		return ;
	//ft_lexer(cmd);
	//ft_tokenize(cmd);
}
// void	ft_lexer(t_cmd *cmd)
// {
	
// }
