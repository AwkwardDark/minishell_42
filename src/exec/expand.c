/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:37:07 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/10 19:01:30 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_extract_exp(char *str, int len)
{
	char *pre_exp;

	pre_exp = ft_calloc(sizeof(char), len + 1);
	if (!pre_exp)
		return (ft_error(7), NULL);
	pre_exp = ft_strncpy(pre_exp, str, len);
	return (pre_exp);
}

char *ft_create_new_expansion(char *str, int i, char *expanded, int new_len)
{
	char *temp;
	char *new;

	temp = ft_calloc(sizeof(char), new_len + 1);
	if (!temp)
		return (NULL);
	temp = ft_strncpy(temp, str, i);
	new = ft_strjoin(temp, expanded);
	free(temp);
	return (new);
}

void ft_expand(t_token *lst, t_env *env)
{
	t_token *current;
	char *str;
	int *exp_tab;
	int exp_tab_len;
	char *pre_exp;
	char *expanded;
	char *new_temp;
	char *new;
	int i;
	int j;
	int new_len;

	current = lst;
	while (current)
	{
		if (current->token_type == WORD && ft_count_exp(current->content) > 0)
		{
			exp_tab = current->pre_expand;
			exp_tab_len = ft_count_exp(str);
			str = current->content;
			i = 0;
			j = 0;
			while (str[i])
			{
				if (str[i] == DOLLAR && exp_tab[j] != -1)
				{
					pre_exp = ft_extract_exp(str + i + 1, exp_tab[j]);
					expanded = ft_find_exp_value(pre_exp, env);
					free(pre_exp);
					new_len = ft_strlen(str) + ft_strlen(expanded) - exp_tab[j] - 1;
					if (new_len == 0)
						new_len = 1;
					new_temp = ft_create_new_expansion(str, i, expanded, new_len);
					new = ft_strjoin(new_temp, str + i + exp_tab[j] + 1);
					free(new_temp);
					if (ft_strlen(expanded) > 1)
						i += ft_strlen(expanded) - 1;
					free(str);
					str = new;
					if (j < exp_tab_len)
						j++;
				}
				if (str[i] && str[i] == DOLLAR && j < exp_tab_len && exp_tab[j] == -1)
				{
					i++;
					j++;
				}
				else if (str[i])
					i++;
			}
			if (new)
			{
				current->content = ft_strdup(new);
				free(new);
			}
		}
		free(current->pre_expand);
		current = current->next;
	}
}
