/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:43:01 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/18 17:46:26 by pbeyloun         ###   ########.fr       */
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
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str != '=' && *str)
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
			errorcmd_failed2("export", token->content, "not a valid identifier");
			data->exit_status = 1;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

static void	display_order(t_data *data, int fd)
{
	t_env	*env;

	env = data->env;
	if (!env)
		return ;
	while (env != NULL)
	{
		ft_putstr_fd("export ", fd);
		ft_putstr_fd(env->key, fd);
		ft_putstr_fd("=", fd);
		if (env->value)
		{
			if (!*env->value)
				ft_putstr_fd("\"\"", fd);
			else
				ft_putstr_fd(env->value, fd);
		}
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
	data->exit_status = 0;
}

void	ft_export(t_data *data, t_token *token, int fd)
{
	int		i;

	i = 0;
	if (!token || token->token_type != WORD)
		display_order(data, fd);
	if (!check_params(token, data))
		return ;
	while (token != NULL)
	{
		if (!strchr(token->content, '='))
			add_or_replace(&data->env, ft_strdup(token->content), ft_strdup(""));
		else
		{
			while (token->content[i] != '=')
				i++;
			add_or_replace(&data->env, ft_strndup(token->content, i), ft_strdup(&token->content[i + 1]));
		}
		i = 0; 
		token = token->next;
	}
}

