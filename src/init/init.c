/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:35:25 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 16:26:28 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**ft_copy_env(char **envp)
{
	char	**env_copy;
	int		i;
	
	i = 0;
	while (envp[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)	
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

int	ft_init_data(char **envp, t_data *data)
{
	
	if (!envp || !envp[0])
		data->env = NULL;
	else
	{
		data->env = ft_copy_env(envp);
		if (!data->env)
			return (ft_error(2), 1);
	}
	data->exit_status = 0;
	return (0);
}
