/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:31:13 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/28 18:08:38 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "" */

#include "builtin.h"

static int	var_exist(char *var, char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (i);
		i++;
	}
	return (-1);
}

static int	alloc_copy(char **new_env, char **old_env, int pos)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_env[i] != NULL)
	{
		if (i != pos)
		{
			new_env[j] = ft_strdup(old_env[i]);
			if (!new_env[j])
				return (j - 1);
			j++;
		}
		i++;
	}
	new_env[i] = 0;
	return (-1);
}

static void	envvar_remove(t_data *data, int pos)
{
	int		env_len;
	char	**new_env;
	int		ret;

	env_len = 0;
	while (data->env[env_len])
		env_len++;
	new_env = (char **)malloc(sizeof(char *) * (env_len));
	if (!new_env)
		return ;
	ret = alloc_copy(new_env, data->env, pos);
	if (ret >= 0)
	{
		while (ret >= 0)
		{
			free(new_env[ret]);
			ret--;
		}
		free(new_env);
		return ;
	}
	data->env = new_env;
}

void	ft_unset(char *var, t_data *data)
{
	int	pos;

	if (!var)
		return ;
	if (!*var)
		return ;
	pos = var_exist(var, data->env);
	if (pos >= 0)
		envvar_remove(data, pos);
	char **new_env = data->env;
}