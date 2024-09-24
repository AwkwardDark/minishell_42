/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:43:01 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/24 15:41:56 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	searches in export and env for the key
	if its found free value and replace it with new
	or creates a new node with key and value
*/
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
			if (cur->value)
				free(cur->value);
			cur->value = value;
			return ;
		}
		cur = cur->next;
	}
	ft_addlstenv(env, key, value);
}

/*
	checks if the key for the export starts with an Alphabetical value
	or '_' and if the reste of the key is alphabetical or numeric
*/
static int	check_params(t_token *token, t_data *data)
{
	while (token != NULL)
	{
		if (!keyparse(token->content))
		{
			errorcmd_failed2("export", token->content,
				"not a valid identifier");
			data->exit_status = 1;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

// dispays the output for the export command alone
static void	display_ordered(t_data *data, t_env *env, int fd)
{
	if (!env || ft_putstr2("", fd) < 0)
	{
		data->exit_status = 1;
		return ;
	}
	while (env != NULL)
	{
		ft_putstr2("export ", fd);
		ft_putstr2(env->key, fd);
		if (env->value)
		{
			ft_putstr2("=", fd);
			if (!*env->value)
				ft_putstr2("\"\"", fd);
			else
			{
				ft_putstr2("\"", fd);
				ft_putstr2(env->value, fd);
				ft_putstr2("\"", fd);
			}
		}
		ft_putstr2("\n", fd);
		env = env->next;
	}
	data->exit_status = 0;
}

// sorts the export in the ascii ordered
static void	display_asciordr(t_env *env, t_data *data, int fd)
{
	t_env	*temp;
	t_env	*temp1;
	char	*keytemp;
	char	*valuetemp;

	temp = env;
	while (temp != NULL)
	{
		temp1 = temp->next;
		while (temp1)
		{
			if (ft_strcmp(temp->key, temp1->key) > 0)
			{
				keytemp = temp->key;
				valuetemp = temp->value;
				temp->key = temp1->key;
				temp->value = temp1->value;
				temp1->key = keytemp;
				temp1->value = valuetemp;
			}
			temp1 = temp1->next;
		}
		temp = temp->next;
	}
	display_ordered(data, env, fd);
}

// handles the export builtin
void	ft_export(t_data *data, t_token *token, int fd)
{
	int		i;

	i = 0;
	if (!token || token->token_type != WORD)
		display_asciordr(data->export, data, fd);
	if (!check_params(token, data))
		return ;
	while (token != NULL)
	{
		if (!strchr(token->content, '='))
			add_or_replace(&data->export, ft_strdup(token->content), NULL);
		else
		{
			while (token->content[i] != '=')
				i++;
			add_or_replace(&data->env, ft_strndup(token->content, i),
				ft_strdup(&token->content[i + 1]));
			add_or_replace(&data->export, ft_strndup(token->content, i),
				ft_strdup(&token->content[i + 1]));
		}
		i = 0;
		token = token->next;
	}
}
