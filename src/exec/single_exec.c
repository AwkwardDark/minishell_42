/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:36:14 by pierre            #+#    #+#             */
/*   Updated: 2024/09/23 15:33:46 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parses error in case the excve fails
static void	parse_error2(char *path, t_data *data, t_token *token, char **argv)
{
	if (is_directory(path))
		isdirectory_exit(argv, data, token, 126);
	permissiond_exit(token->content, data, argv, NULL);
}

// parses error in case there was no path found for the exec
static void	parse_error1(char *path, t_token *token,
	t_data *data, char **argv)
{
	if (!access(path, F_OK) && is_directory(path))
		isdirectory_exit(argv, data, token, 126);
	if (ft_strchr(path, '/'))
		nosuchfile_exit(argv, data, token, 126);
	cmdnotfound_exit(argv, data, token, 127);
}

void	executer(t_data *data, t_token *token)
{
	char	*path;
	char	**argv;
	char	**env_arr;

	if (!ft_strcmp(token->content, "") && token->next == NULL)
		exit_success(data);
	if ((!access(token->content, F_OK) || !ft_strcmp(token->content, ""))
		&& ft_strchr(token->content, '/'))
	{
		path = token->content;
		argv = cmdlst_tocmdarr(token);
	}
	else
	{
		argv = cmdlst_tocmdarr(token);
		path = test_path(get_paths(data->env), token->content);
	}
	if (!path)
		parse_error1(token->content, token, data, argv);
	env_arr = lstenv_towordarr(data->env);
	if (execve(path, argv, env_arr) < 0)
	{
		clear_wordar(env_arr);
		parse_error2(path, data, token, argv);
	}
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

	if (!envpath)
		return (NULL);
	i = 0;
	cmd_len = ft_strlen(cmd);
	paths = ft_split(envpath, ':');
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
