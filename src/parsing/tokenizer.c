/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:49:48 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/19 15:19:26 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It verifies basic syntax on quotes, operators and parenthesis,
then it creates a double linked list where each node is separated by an space
or and special symbol (lexer). Then it tokenize each node (tokenizer), and 
lastly it checks if the grammar between each node is correct (parser).
Once lexer, tokenizer and parser its done, it checks for expand, wildcard and
redirections, it also remove the quotes*/
int	ft_parser(char *input, t_data *data)
{
	if (ft_quote_syntax(input) == 1)
		return (ft_error(0), data->lst_exit_status = 2, 0);
	if (ft_operator_syntax(input, data) == 1)
		return (0);
	if (ft_parenthesis_syntax(input, data) == 1)
		return (ft_error(5), data->lst_exit_status = 2, 0);
	ft_lexer(input, data);
	if (!data->token_lst)
		return (0);
	ft_tokenize(data->token_lst);
	if (ft_grammar_syntax(data->token_lst, data))
	{
		ft_putstr_fd(RED"minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(data->syntax_error, 2);
		ft_putstr_fd("'\n"RESET, 2);
		data->lst_exit_status = 2;
		return (0);
	}
	ft_pre_expand(data->token_lst);
	ft_pre_wildcard(data->token_lst);
	ft_remove_quotes(data->token_lst, data);
	ft_redir_check(&data->token_lst);
	return (1);
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
		if (ft_is_operator(input, i, data))
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

/*It tokenizes each node dependint on its content*/
void	ft_tokenize(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current)
	{
		if (ft_is_symbol(current->content[0]))
			ft_token_symbol(current->content, current);
		else
			current->token_type = WORD;
		current = current->next;
	}
}
