/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:37:07 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/11 14:52:37 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_extract_exp(char *str, int len)
{
	char	*pre_exp;

	pre_exp = ft_calloc(sizeof(char), len + 1);
	if (!pre_exp)
		return (ft_error(7), NULL);
	pre_exp = ft_strncpy(pre_exp, str, len);
	return (pre_exp);
}

static char	*ft_create_new_expansion(char *str, int i, char *expanded, int n_l)
{
	char	*temp;
	char	*new;

	temp = ft_calloc(sizeof(char), n_l + 1);
	if (!temp)
		return (NULL);
	temp = ft_strncpy(temp, str, i);
	new = ft_strjoin(temp, expanded);
	free(temp);
	return (new);
}
/*It doesnt work with the norm*/
static char	*ft_calc_expan(char *str, t_env *env, int *i, int *j, t_token *curr)
{
	char	*pre_exp;
	char	*expanded;
	char	*new_temp;
	char	*new;
	int		new_len;

	pre_exp = ft_extract_exp(str + *i + 1, curr->pre_expand[*j]);
	expanded = ft_find_exp_value(pre_exp, env);
	free(pre_exp);
	new_len = ft_strlen(str) + ft_strlen(expanded) - curr->pre_expand[*j] - 1;
	if (new_len == 0)
		new_len = 1;
	new_temp = ft_create_new_expansion(str, *i, expanded, new_len);
	new = ft_strjoin(new_temp, str + *i + curr->pre_expand[*j] + 1);
	free(new_temp);
	if (ft_strlen(expanded) > 1)
		*i += ft_strlen(expanded) - 1;
	free(str);
	str = ft_strdup(new);
	free (new);
	if (*j < curr->exp_tab_len)
		(*j)++;
	return (str);
}

static char	*ft_str_to_exp(char *str, t_env *env, t_token *curr)
{
	int		i;
	int		j;
	int		*tab;

	i = 0;
	j = 0;
	tab = curr->pre_expand;
	while (str[i])
	{
		if (str[i] == DOLLAR && tab[j] != -1)
			str = ft_calc_expan(str, env, &i, &j, curr);
		if (str[i] && str[i] == '$' && j < curr->exp_tab_len && tab[j] == -1)
		{
			i++;
			j++;
		}
		else if (str[i] && str[i] != DOLLAR)
			i++;
	}
	return (str);
}

void	ft_expand(t_token *lst, t_env *env)
{
	t_token	*current;
	char	*result;

	current = lst;
	while (current)
	{
		if (current->token_type == WORD && ft_count_exp(current->content) > 0)
		{
			result = ft_str_to_exp(current->content, env, current);
			if (result)
			{
				current->content = ft_strdup(result);
				free(result);
			}
		}
		free(current->pre_expand);
		current = current->next;
	}
}
