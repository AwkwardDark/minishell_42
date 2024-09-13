/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:43:42 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/13 16:54:23 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// init_env
t_env	*ft_initenv(char *key, char *value)
{
	t_env	*env;

	env = (struct s_env *)malloc(sizeof(struct s_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

// add last
void	ft_addlstenv(t_env **env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*cur;

	if (!*env)
	{
		*env = ft_initenv(key, value);
		return ;
	}
	cur = *env;
	new_env = ft_initenv(key, value);
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new_env;
	cur = *env;
}

/*free all the chained list*/
void	ft_clrenv(t_env **head)
{
	t_env	*cur;
	t_env	*temp;

	cur = *head;
	while (cur != NULL)
	{
		temp = cur;
		cur = cur->next;
		ft_clrenvnode(temp);
	}
	*head = NULL;
}

// free one node
void	ft_clrenvnode(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}
