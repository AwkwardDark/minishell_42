/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:37:28 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/21 01:15:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

// +2 in the malloc because '=' and '\0' TODO
static void	alloc_keyvalue(t_env *env, char **word_arr, int len)
{
	t_env	*temp;
	int		i;

	i = 0;
	temp = env;
	while (i < len)
	{
		word_arr[i] = (char *)malloc(sizeof(char)
				* (ft_strlen(temp->key) + ft_strlen(temp->value) + 2));
		if (!word_arr[i])
			printf("error\n");
		word_arr[i][0] = 0;
		ft_strcat(word_arr[i], temp->key);
		ft_strcat(&word_arr[i][ft_strlen(temp->key)], "=");
		if (temp->value)
			ft_strcat(&word_arr[i][ft_strlen(temp->key) + 1], temp->value);
		temp = temp->next;
		i++;
	}
	word_arr[i] = NULL;
}

char	**lstenv_towordarr(t_env *env)
{
	int		len;
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

static void	alloc_cmds(t_token *token, char **cmd_arr, int len, int absolut)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = token;
	while (i < len)
	{
		if (temp->token_type == WORD)
		{
			alloc_cmds_aux(cmd_arr, temp, i, absolut);
			i++;
		}
		temp = temp->next;
	}
	cmd_arr[i] = NULL;
}

char	**cmdlst_tocmdarr(t_token *token, int absolut)
{
	int		len;
	t_token	*temp;
	char	**arr_cmd;

	temp = token;
	len = 0;
	while (temp != NULL)
	{
		if (temp->token_type == WORD)
			len++;
		temp = temp->next;
	}
	if (len == 0)
		return (NULL);
	arr_cmd = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr_cmd)
		return (NULL);
	temp = token;
	alloc_cmds(token, arr_cmd, len, absolut);
	return (arr_cmd);
}

/* void	ft_print_lst(t_token *lst)
{
	int		i;
	t_token	*current;

	i = 0;
	current = lst;
	if (!lst)
		return ;
	while (current)
	{
		if ((current->token_type == R_IN) || (current->token_type == R_OUT) ||
			(current->token_type == HEREDOC) || (current->token_type == APPEND))
			printf("\n");
		printf("n%d -> %s ----", i, current->content);
		printf(" token -> %d\n", current->token_type);
		if (current->redir)
			printf(" ~~~ redir file -> %s ~~~\n\n", current->redir);
		current = current->next;
		i++;
	}
	while (lst != NULL)
	{
		printf("%s", lst->content);
		lst = lst->next;
	}
	printf("\n");
} */
