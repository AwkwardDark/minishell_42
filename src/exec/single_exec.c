/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 21:36:14 by pierre            #+#    #+#             */
/*   Updated: 2024/09/04 15:33:08 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	function that will execute a single command it's basicaly the exec part
	of pipex but with different arguments, TODO exit status with the signal (128 + signal)
	this function most be called by a chld process the redirectiosn most be made before !!
	the t_pipe data
 */
void	executer(t_env *env, t_token *token)
{
	char	*path;
	char	**argv;
	char	**env_arr;

	if (!access(token->content, F_OK))
		path = token->content;
	else
	{
		argv = cmdlst_tocmdarr(token); // TODO see how we will get this data !
		path = test_path(get_paths(env), token->content);
		if (!path)
		{
			clear_wordar(argv);
			// error_disp_exit("pipex: ", argv[0], "command not found", 127);
		}
	}
	env_arr = lstenv_towordarr(env);
	if (execve(path, argv, env_arr) < 0)
	{
		free(path);
		free(env);
		clear_wordar(argv);
		// error_disp_exit("pipex: ", "", strerror(errno), 126);
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

/* malloc() to concatenate path + '/' + cmd*/
char	*add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * (cmd_len + ft_strlen(paths[idx]) + 2));
	if (!path)
	{
		clear_wordar(paths);
		return (NULL);
	}
	path[0] = 0;
	ft_strcat(path, paths[idx]);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}

// +2 in the malloc because '=' and '\0'
static void	alloc_keyvalue(t_env *env, char **word_arr, int len)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while (i < len)
	{
		word_arr[i] = (char *)malloc(sizeof(char) * (ft_strlen(temp->key) + ft_strlen(temp->value) + 2));
		if (!word_arr[i])
			// TODO
		word_arr[i][0] = 0;
		ft_strcpy(word_arr[i], temp->key);
		ft_strcpy(&word_arr[i][ft_strlen(temp->key)], "=");
		ft_strcpy(&word_arr[i][ft_strlen(temp->key) + 1], temp->value);
		temp = temp->next;
		i++;
	}
	word_arr[i] = NULL;
}
char	**lstenv_towordarr(t_env *env)
{
	int	len;
	t_env	*temp;
	char	**arr_env;

	temp = env;
	len = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		len++;
	}
	if (len == 0)
		return (NULL);
	arr_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr_env)
		return (NULL);
	alloc_keyvalue(env, arr_env, len);
	return (arr_env);
}

static void	alloc_cmds(t_token *token, char **cmd_arr, int len)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = token;
	while (i < len)
	{
		cmd_arr[i] = (char *)malloc(sizeof(char) * (ft_strlen(temp->content) + 1));
		if (!cmd_arr[i])
			// TODO
		cmd_arr[i][0] = 0;
		ft_strcpy(cmd_arr[i], temp->content);
		temp = temp->next;
		i++;
	}
	cmd_arr[i] = NULL;
}

char	**cmdlst_tocmdarr(t_token *token)
{
	int		len;
	t_token	*temp;
	char	**arr_cmd;

	temp = token;
	len = 0;
	while (temp != NULL && temp->token_type == WORD)
	{
		temp = temp->next;
		len++;
	}
	if (len == 0)
		return (NULL);
	arr_cmd = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr_cmd)
		return (NULL);
	temp = token;
	alloc_cmds(token, arr_cmd, len);
	return (arr_cmd);
}
