/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:43:01 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/19 15:44:56 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	display_ordered(t_data *data, t_env *env, int fd)
{
	if (!env)
		return ;
	while (env != NULL)
	{
		ft_putstr_fd("export ", fd);
		ft_putstr_fd(env->key, fd);
		if (env->value)
		{
			ft_putstr_fd("=", fd);
			if (!*env->value)
				ft_putstr_fd("\"\"", fd);
			else
			{
				ft_putstr_fd("\"", fd);
				ft_putstr_fd(env->value, fd);
				ft_putstr_fd("\"", fd);
			}
		}
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
	data->exit_status = 0;
}

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
