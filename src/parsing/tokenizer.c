/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:49:48 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/04 19:07:10 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It verifies basic syntax on quotes, operators and parenthesis,
then it creates a double linked list where each node is separated by an space
or and special symbol. Then it tokenize each node, and lastly it checks if
the grammar between each node is correct*/
void	ft_parser(char *input, t_data *data)
{	
	if (ft_quote_syntax(input) == 1)
		return (ft_error(0));
	if (ft_operator_syntax(input, data) == 1)
		return ;
	if (ft_parenthesis_syntax(input, data) == 1)
		return (ft_error(5));
	ft_lexer(input, data);
	ft_tokenize(data->token_lst);
	if (ft_grammar_syntax(data->token_lst, data))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(data->syntax_error, 2);
		ft_putstr_fd("'\n", 2);
		return ;
	}
	//...
}
/*If there are quotes it will be in the same node, a special symbol (operator)
is stocked in a new node*/
static void	ft_isolate_node(char *input, t_data *data, int *i)
{
	while (input[*i] != ' ' && input[*i])
	{
		if (ft_is_quote(input[*i], data))
		{
			while (input[*i + 1] != data->quote_type)
				(*i)++;
			(*i)++;
		}
		if (ft_is_special(input, i, data))
			break ;
		(*i)++;
	}
}

/*It will create a double linked list where each node contains the
content and token_type of each word/operator of the prompt command*/
void	ft_lexer(char *input, t_data *data)
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
		ft_isolate_node(input, data, &i);
		end = i;
		content = ft_strndup(input + start, end - start);
		ft_lstadd_back(&data->token_lst, ft_lstnew(content));
	}
}

void	ft_tokenize(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current != NULL)
	{
		if (ft_is_symbol(current->content[0]))
			ft_token_symbol(current->content, current);
		else
			current->token_type = WORD;
		current = current->next;
	}
	ft_print_lst(lst);
}
