/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:36:14 by pierre            #+#    #+#             */
/*   Updated: 2024/09/13 15:32:59 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	function that will execute a single command it's basicaly 
	the exec part of pipex but with different arguments, 
	TODO exit status with the signal (128 + signal)
	this function most be called by a chld process the 
	redirectiosn most be made before !!
	the t_pipe data TODO
 */
void	executer(t_data *data, t_token *token)
{
	char	*path;
	char	**argv;
	char	**env_arr;

	if (!ft_strncmp(token->content, "./", 2) && !access(token->content, F_OK | X_OK))
	{
		path = token->content;
		argv = cmdlst_tocmdarr(token, 1);
	}
	else
	{
		if (!ft_strncmp(token->content, "./", 2) && access(token->content, X_OK))
			permissiond_exit(token->content, data);
		path = test_path(get_paths(data->env), token->content);
		argv = cmdlst_tocmdarr(token, 0);
		if (!path || !ft_strcmp(*argv, ""))
			cmdnotfound_exit(argv, data, token, 127);
	}
	env_arr = lstenv_towordarr(data->env);
	if (execve(path, argv, env_arr) < 0)
		free_exec(path, argv, env_arr);
}

/* returns a Pointer to whats after "PATH=" in the env */
char	*get_paths(t_env *env)
{
	if (!env)
		return (NULL);
	else
	{
		while (env != NULL)
		{
			if (!ft_strcmp(env->key, "PATH"))
				return (env->value);
			env = env->next;
		}
	}
	return (NULL);
}

/* searches for a Path to the executable using access */
char	*test_path(char *envpath, char *cmd)
{
	char	*path;
	char	**paths;
	int		cmd_len;
	int		i;

	i = 0;
	cmd_len = ft_strlen(cmd);
	paths = ft_split(envpath, ':');
	if (!envpath)
		return (NULL);
	while (paths[i])
	{
		path = add_cmdtopath(paths, cmd, cmd_len, i);
		if (!path)
			return (NULL);
		if (!access(path, F_OK))
		{
			clear_wordar(paths);
			return (path);
		}
		free(path);
		i++;
	}
	clear_wordar(paths);
	return (NULL);
}
