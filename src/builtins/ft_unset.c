/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:46:55 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/19 15:37:39 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "" */

#include "minishell.h"

static void	remove_node(char *key, t_env **env)
{
	t_env	*prev;
	t_env	*cur;

	cur = *env;
	prev = cur;
	if (!ft_strcmp(cur->key, key))
	{
		*env = cur->next;
		ft_clrenvnode(cur);
		return ;
	}
	while (cur != NULL)
	{
		if (!ft_strcmp(cur->key, key))
		{
			prev->next = cur->next;
			ft_clrenvnode(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	ft_unset(t_token *token, t_data *data)
{
	if (token == NULL || token->token_type != WORD)
		return ;
	while (token != NULL && token->token_type == WORD)
	{
		remove_node(token->content, &data->env);
		remove_node(token->content, &data->export);
		token = token->next;
	}
}
