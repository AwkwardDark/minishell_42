/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:46:55 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/30 14:39:06 by pbeyloun         ###   ########.fr       */
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
	while (cur != NULL && ft_strcmp(cur->key, key) != 0)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur != NULL)
	{
		prev->next = cur->next;
		ft_clrenvnode(cur);
	}
}

void	ft_unset(char *key, t_data *data)
{
	if (!key)
		return ;
	if (!*key)
		return ;
	remove_node(key, &data->env);
}
