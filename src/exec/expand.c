/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:37:07 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/09 19:00:47 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_extract_exp(char *str, int len)
{
	char *new;

	new = ft_calloc(sizeof(char), len + 1);
	if (!new)
		return (ft_error(7), NULL);
	new = ft_strncpy(new, str, len);
	return (new);
}

char *ft_create_new_expansion(char *str, int i, char *expanded, int new_len)
{
	char *new;
	int k;

	new = ft_calloc(sizeof(char), new_len);
	if (!new)
		return (NULL);
	k = 0;
	new = ft_strncpy(new, str, i);
	new = ft_strjoin(new, expanded);
	return (new);
}

void ft_expand(t_token *lst, t_env *env)
{
	t_token *current;
	char *str;
	int *exp_tab;
	char *pre_exp;
	char *expanded;
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
			str = current->content;
			i = 0;
			j = 0;
			while (str[i])
			{
				if (str[i] == DOLLAR && current->pre_expand[j] != -1)
				{
					pre_exp = ft_extract_exp(str + i + 1, exp_tab[j]);
					expanded = ft_find_exp_value(pre_exp, env);
					new_len = ft_strlen(str) + ft_strlen(expanded) - exp_tab[j] - 1;
					new = ft_calloc(sizeof(char), new_len);
					if (!new)
						return;
					new = ft_create_new_expansion(str, i, expanded, new_len);
					//printf("before -> %d\n", i);
					//i += new_len;
					//printf("after -> %d\n", i);
					//printf("%s\n", str);
					new = ft_strjoin(new, str + i + exp_tab[j] + 1);
					printf("%s\n", new);
					i += exp_tab[j];
					j++;
					str = new;
				}
				else
					i++;
			}
			if (new)
			{
				free(current->content);
				current->content = new;
			}
		}
		current = current->next;
	}
}
