/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:32:00 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/18 19:36:20 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*add_defaultenv(void)
{
	char	pwd[500];
	t_env	*env;
	char	*cwd;

	cwd = getcwd(pwd, 500);
	env = NULL;
	if (!cwd)
	{
		ft_putstr_fd(CHDIR_PWD, 2);
		return (NULL);
	}
	ft_addlstenv(&env, ft_strdup("SHLVL"), ft_strdup("1"));
	ft_addlstenv(&env, ft_strdup("PWD"), ft_strdup(cwd));
	return (env);
}

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
	if (!env[i])
		return (add_defaultenv());
	while (env[i])
	{
		while (env[i][j] != '=')
			j++;
		ft_strncpy(key, env[i], j);
		if (!ft_strncmp(key, "SHLVL", j))
			ft_addlstenv(&env_lst, ft_strdup(key),
				ft_itoa((ft_atoi(&env[i][j + 1]) + 1)));
		else
			ft_addlstenv(&env_lst, ft_strdup(key), ft_strdup(&env[i][j + 1]));
		j = 0;
		i++;
	}
	return (env_lst);
}
