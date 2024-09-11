/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:56:01 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/11 12:06:33 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_alone(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] != SPACE && str[*i] != D_QUOTE)
			return (0);
		(*i)++;
	}
	return (1);
}

static int	ft_save_expand(char *str, int *i, int d_flag)
{
	int	pre_expand_len;
	int	k;

	if (str[*i] == '?')
		return (1);
	if ((str[*i] == D_QUOTE || str[*i] == S_QUOTE) && (d_flag != -1))
		return (0);
	if ((!str[*i]) || ft_is_special(str[*i]) || ft_is_alone(str, i))
		return (-1);
	k = *i;
	while (str[*i] && !ft_is_special(str[*i]))
		(*i)++;
	pre_expand_len = *i - k;
	if (pre_expand_len > 0)
		(*i)--;
	return (pre_expand_len);
}

int	ft_count_exp(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR)
			count++;
		i++;
	}
	return (count);
}

static void	ft_create_exp_tab(t_token *cur, char *str, int *s_flag, int *d_flag)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE && *s_flag == 1)
			*d_flag *= -1;
		if (str[i] == S_QUOTE && *d_flag == 1)
			*s_flag *= -1;
		if (str[i] == DOLLAR && *s_flag == 1)
		{
			i++;
			cur->pre_expand[j++] = ft_save_expand(str, &i, *d_flag);
		}
		if (str[i] == DOLLAR && *s_flag == -1)
		{
			i++;
			cur->pre_expand[j++] = -1;
		}
		else if (str[i] && str[i] != DOLLAR)
			i++;
	}
}

void	ft_pre_expand(t_token *lst)
{
	t_token	*current;
	char	*str;
	int		s_flag;
	int		d_flag;

	current = lst;
	s_flag = 1;
	d_flag = 1;
	while (current)
	{
		if (current->token_type == WORD && ft_count_exp(current->content) > 0)
		{
			str = current->content;
			current->pre_expand = ft_calloc(sizeof(int), ft_count_exp(str));
			if (!current->pre_expand)
				return (ft_error(7));
			ft_create_exp_tab(current, str, &s_flag, &d_flag);
			current->exp_tab_len = ft_count_exp(str);
		}
		else
			current->pre_expand = NULL;
		current = current->next;
	}
}
