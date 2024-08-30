/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:49:48 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/30 14:38:04 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/minishell.h"

/*It verifies basic synta on quotes and operators.
Then it tokenize each command based on operator and prioritis.
Finally it ranges each*/
t_token	*ft_parser(char *input, t_data **data)
{	
	t_token *t_token_lst;
	
	if (ft_quote_syntax(input) == 1)
		return(ft_error(0), NULL);
	if (ft_operator_syntax(input) == 1)
		return(ft_error(0), NULL);
	t_token_lst = ft_tokenize(input, data);
	return (t_token_lst);
}

/*It will create a double linked list where each node contains the
content and token_type of each word/operator of the prompt command*/
t_token *ft_tokenize(char *input, t_data *data)
{
	int		i;
	char	*content;

	i = 0;
	while (input[i])
	{
		while (input[i] != ' ')
			i++;
		content = ft_strndup(input, i);
		ft_lst_add_back(&(data->token_lst), ft_lstnew(content));
	}
}
