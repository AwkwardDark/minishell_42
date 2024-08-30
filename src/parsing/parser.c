/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:49:48 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/30 16:03:35 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*It verifies basic synta on quotes and operators.
Then it tokenize each command based on operator and prioritis.
Finally it ranges each*/
void	ft_parser(char *input, t_data *data)
{	
	if (ft_quote_syntax(input) == 1)
		return(ft_error(0));
	// if (ft_operator_syntax(input) == 1)
	// 	return(ft_error(0), NULL);
	ft_tokenize(input, data);
}

/*It will create a double linked list where each node contains the
content and token_type of each word/operator of the prompt command*/
void	ft_tokenize(char *input, t_data *data)
{
	char	*content;
	int		start;
	int		end;
	int		i;
	
	i = 0;
	start = 0;
	end = 0;
	while (input[i])
	{
		while (input[i] == ' ' && input[i])
			i++;
		if (!input[i])
			break ;
		start = i;
		while (input[i] != ' ' && input[i])
			i++;
		end = i;
		content = ft_strndup(input + start, end - start);
		ft_lstadd_back(&data->token_lst, ft_lstnew(content));
	}
}
