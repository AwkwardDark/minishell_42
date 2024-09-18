/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:24:45 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/18 20:17:40 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_norme_quote(int *flag, int *count, int *count_q, int type)
{
	if (type == 1)
	{
		*flag = 1;
		*count *= -1;
		(*count_q)++;
	}
	if (type == 2)
	{
		*flag = 2;
		*count *= -1;
		(*count_q)++;
	}
}

/*This function counts the number of valid quotes (simple or double)*/
static int	ft_c_q(char *input)
{
	int	i;
	int	count;
	int	count_q;
	int	flag;

	i = -1;
	count = 1;
	count_q = 0;
	flag = 0;
	while (input[++i])
	{
		if ((input[i] == S_QUOTE) && (flag == 0 || flag == 1))
			ft_norme_quote(&flag, &count, &count_q, 1);
		if ((input[i] == D_QUOTE) && (flag == 0 || flag == 2))
			ft_norme_quote(&flag, &count, &count_q, 2);
		if (count == 1)
			flag = 0;
	}
	return (count_q);
}
/*It copys the content without the quotes*/
void	ft_create_unquoted(char *old, char *new, int *flag, t_data *data)
{
	while (*old)
	{
		if (*old == data->quote_type)
		{
			old++;
			*flag = 1;
			data->quote_type = '\0';
		}
		if (*flag)
		{
			if (ft_is_quote(*old, data))
			{
				old++;
				*flag = 0;
			}
		}
		if (*old && *old != data->quote_type)
		{
			*new = *old;
			old++;
			new++;
		}
	}
}

/*It frees the old content and build the new content without the valid quotes*/
void	ft_remove_quotes(t_token *lst, t_data *data)
{
	t_token	*current;
	char	*new;
	char	*old;
	int		flag;

	current = lst;
	while (current)
	{
		current->quote_flag = 0;
		if ((current->token_type == WORD) && ft_str_is_quote(current->content))
		{
			old = current->content;
			current->quote_flag = 1;
			new = ft_calloc(sizeof(char), (ft_strlen(old) - ft_c_q(old) + 1));
			if (!new)
				return (ft_error(7));
			flag = 1;
			data->quote_type = '\0';
			ft_create_unquoted(old, new, &flag, data);
			free(current->content);
			current->content = new;
		}
		current = current->next;
	}
}
