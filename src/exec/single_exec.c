/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:36:14 by pierre            #+#    #+#             */
/*   Updated: 2024/09/20 15:16:34 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_slashdots(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '.' || *cmd == '/')
			cmd++;
		else
			return (0);
	}
	return (1);
}

/* 
will check if there is any of the following errors:
	127: command not found
	127: no such file or directory
	126: permission denied
*/
static void	check_validity(char *path, t_token *token,
	t_data *data, char **argv)
{
	if ((path && access(path, X_OK) && !access(path, F_OK))
		|| (access(token->content, X_OK) && !access(token->content, F_OK)))
		permissiond_exit(token->content, data, argv, path);
	if (!path || !ft_strcmp(*argv, ""))
	{
		if (ft_strchr(token->content, '/') || ft_strchr(token->content, '.'))
		{
			if (!access(token->content, R_OK))
				isdirectory_exit(argv, data, token, 126);
			nosuchfile_exit(argv, data, token, 126);
		}
		cmdnotfound_exit(argv, data, token, 127);
	}
}

// executes command and handles erros 
void	executer(t_data *data, t_token *token)
{
	char	*path;
	char	**argv;
	char	**env_arr;

	if (!ft_strncmp(token->content, "./", 2) && ft_strlen(token->content) > 2
		&& !is_slashdots(&token->content[2]) && !access(token->content,
			F_OK | X_OK))
	{
		path = token->content;
		argv = cmdlst_tocmdarr(token, 1);
	}
	else
	{
		path = test_path(get_paths(data->env), token->content);
		argv = cmdlst_tocmdarr(token, 0);
		check_validity(path, token, data, argv);
	}
	close_fds(data->bin);
	env_arr = lstenv_towordarr(data->env);
	if (execve(path, argv, env_arr) < 0)
		free_execve(path, argv, env_arr);
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

	if (!envpath || is_slashdots(cmd))
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
