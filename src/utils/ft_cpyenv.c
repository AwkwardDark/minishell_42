/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:32:00 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/29 16:04:05 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_cpyenv(char **env)
{
	t_env	*env_lst;
	char	key[300];
	int		i;
	int		j;

	env_lst = NULL;
	ft_bzero(key, 300);
	j = 0;
	i = 0;
	while (env[i])
	{
		while (env[i][j] != '=')
			j++;
		ft_strncpy(key, env[i], j);
		ft_addlstenv(&env_lst, ft_strdup(key), ft_strdup(&env[i][j + 1]));
		j = 0;
		i++;
	}
	return (env_lst);
}
