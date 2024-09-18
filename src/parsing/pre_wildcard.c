/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_wildcard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:07:09 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/18 23:45:23 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Verifies that * is not on a quoted portion of the char*/
static int	ft_check_wild(char *str)
{
	int	i;
	int	flag;
	int	count;

	i = -1;
	flag = 0;
	count = 1;
	while (str[++i])
	{
		if ((str[i] == S_QUOTE) && (flag == 0 || flag == 1))
		{
			flag = 1;
			count *= -1;
		}
		if ((str[i] == D_QUOTE) && (flag == 0 || flag == 2))
		{
			flag = 2;
			count *= -1;
		}
		if (count == 1)
			flag = 0;
		if ((flag == 0) && (str[i] == '*'))
			return (1);
	}
	return (0);
}

/*It cheks if the content of each token contains a valid * (nor quoted)*/
void	ft_pre_wildcard(t_token *lst)
{
	t_token	*current;

	current = lst;
	while (current)
	{
		current->wildcard = 0;
		if (current->token_type == WORD && ft_check_wild(current->content))
			current->wildcard = 1;
		current = current->next;
	}
}
