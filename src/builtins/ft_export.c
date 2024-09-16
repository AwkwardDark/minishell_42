/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:43:01 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/16 18:37:25 by pbeyloun         ###   ########.fr       */
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
		return ;
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
