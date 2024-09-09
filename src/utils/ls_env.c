/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:43:42 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/09 18:15:44 by pajimene         ###   ########.fr       */
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

// Finds for the expansion value of an enviroment variable
char	*ft_find_exp_value(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

// free one node
void	ft_clrenvnode(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}
