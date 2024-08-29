/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:43:42 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/29 12:16:21 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_env *init_env(char *key, char *value)
{
	t_env *env;

	env = (struct s_env*)malloc(sizeof(struct s_env));
	if (!env)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
}

void	addlst_envvar(t_env **env, char *key, char *value)
{
	t_env	*new_env;
	t_env	*cur;

	if (!*env)
		return ;
	cur = *env;
	new_env = init_env(key, value);
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new_env;
}

void	clr_env(t_env **head)
{
	t_env	*cur;
	t_env	*temp;

	cur = *head;
	while (cur != NULL)
	{
		temp = cur;
		cur = cur->next;
		clr_envnode(temp);
	}
	*head = NULL;
}

void	clr_envnode(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}