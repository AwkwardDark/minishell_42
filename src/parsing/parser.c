/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:49:48 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 18:11:33 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

/*It verifies basic synta on quotes and operators.
Then it tokenize each command based on operator and prioritis.
Finally it ranges each*/
void	ft_parser(char *input, t_data *data)
{	
	t_token *t_token_lst;
	
	if (ft_quote_syntax(input) == 1)
		return(ft_error(0));
	if (ft_operator_syntax(input) == 1)
		return(ft_error(0));
	t_token_lst = ft_tokenize(input, data);
}
t_token *ft_tokenize(char *input, t_data *data)
{
	t_token	first_token;
	int		i;

	i = 0;
	while (input[i])
	{
		
	}
}
