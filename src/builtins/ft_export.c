/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:43:01 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/17 12:08:06 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO In special parsing of the export check that the format 
	of export is right
	export key="value" => good
	export key=value => good
	export key = value => wrong
	and display error messages
*/

static int	keyparse(char *str)
{
	if (!ft_strchr(str, '='))
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str != '=')
	{
		if (!ft_isdigit(*str) && !ft_isalpha(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	add_or_replace(t_env **env, char *key, char *value)
{
	t_env	*cur;

	cur = *env;
	if (!cur)
	{
		*env = ft_initenv(key, value);
		return ;
	}
	while (cur != NULL)
	{
		if (!ft_strcmp(cur->key, key))
		{
			free(key);
			free(cur->value);
			cur->value = value;
			return ;
		}
		cur = cur->next;
	}
	ft_addlstenv(env, key, value);
}

void	ft_export(t_data *data, t_token *token)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (!token || token->token_type != WORD)
		display_order(data);
	else if (!keyparse(token->content))
	{
		ft_putstr_fd("error\n", 2);
		data->exit_status = 1;
	}
	else
	{
		while (token->content[i] != '=')
			i++;
		key = ft_strndup(token->content, i);
		value = ft_strdup(&token->content[i + 1]);
		add_or_replace(&data->env, key, value);
	}
}

void	display_order(t_data *data)
{
	t_env	*env1;
	t_env	*env2;
	char	*tempk;
	char	*tempv;

	env1 = data->env;
	env2 = data->env;
	while (env2 != NULL)
	{
		while (env1 != NULL)
		{
			if (ft_strcmp(env2->key, env1->key) > 0)
			{
				tempk = env1->key;
				tempv = env1->value;
				env1->key = env2->key;
				env1->value = env2->value;
				env2->key = tempk;
				env2->value = tempv;
			}
			env1 = env1->next;
		}
		env2 = env2->next;
	}
	ft_env(data, 1);
}
