/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:31:13 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/29 12:24:47 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "" */

#include "builtin.h"

static void	remove_node(char *key, t_env **env)
{
	t_env	*prev;
	t_env	*cur;

	cur = *env;
	prev = cur;
	if (!ft_strcmp(cur->key, key))
	{
		*env = cur->next;
		clr_envnode(cur);
		return ;
	}
	while (cur != NULL && ft_strcmp(cur->key, key))
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur != NULL)
	{
		prev = cur->next;
		clr_envnode(cur);
	}
}


void	ft_unset(char *key, t_data *data)
{
	int	pos;

	if (!key)
		return ;
	if (!*key)
		return ;
	remove_node(key, &data->env);
}