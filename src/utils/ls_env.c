/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:43:42 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/18 17:07:11 by pbeyloun         ###   ########.fr       */
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

// Finds for the expansion value of an enviroment variable
char	*ft_find_exp_value(char *key, t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(key, "?"))
		{
			data->free_flag = 1;
			if (g_signal == 0)
				return (ft_itoa(data->lst_exit_status));
			else
				return (ft_itoa(g_signal + 128));
		}
		if (!ft_strcmp(key, current->key))
		{
			data->free_flag = 0;
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

// free one node
void	ft_clrenvnode(t_env *env)
{
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

// searches for the value of a key in env returns NULL if key doesnt exist
char	*get_env(t_env *env, char *key)
{
	char	*val;

	val = NULL;
	if (!env)
		return (val);
	while (env != NULL)
	{
		if (!ft_strcmp(env->key, key))
		{
			val = env->value;
			break ;
		}
		env = env->next;
	}
	return (val);
}
