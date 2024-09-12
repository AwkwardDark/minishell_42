/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:57:07 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/12 18:54:47 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_simple_wildcard(char *wildcard)
{
	int	i;

	i = 0;
	while (wildcard[i])
	{
		if (wildcard[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_char_in_str(char c, char *entry, int *j)
{
	if (c == '\0')
		return (1);
	while (entry[*j])
	{
		if (entry[*j] == c)
			return (1);
		(*j)++;
	}
	return (0);
}

static int	ft_wild_match(char *entry, char *wildcard)
{
	int	i;
	int	j;

	if (ft_simple_wildcard(wildcard))
		return (1);
	if ((wildcard[ft_strlen(wildcard) - 1] != '*') && (wildcard[ft_strlen(wildcard) - 1] != entry[ft_strlen(entry) - 1]))
		return (0);
	i = 0;
	j = 0;
	while (wildcard[i])
	{
		while (wildcard[i] && wildcard[i] != '*')
			i++;
		if (ft_strncmp(wildcard, entry, i))
			return (0);
		while (wildcard[i] && wildcard[i] == '*')
			i++;
		while (wildcard[i] && wildcard[i] != '*')
		{
			if (!ft_char_in_str(wildcard[i], entry, &j))
				return (0);
			i++;
			if (ft_simple_wildcard(wildcard + i))
				return (1);
		}
	}
	return (1);
}

static void	ft_expand_wildcard(t_token *current, int *delete_flag)
{
	struct dirent	*entry;
	DIR				*dirp;
	t_token			*wild_node;

	dirp = opendir(".");
	entry = readdir(dirp);
	wild_node = current;
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			if (ft_wild_match(entry->d_name, current->content))
			{
				*delete_flag = 1;
				ft_insert_after(current, ft_lstnew(ft_strdup(entry->d_name)));
			}
		}
		entry = readdir(dirp);
	}
	closedir(dirp);
}

void	ft_wildcard(t_token **lst, t_data *data)
{
	t_token	*current;
	t_token	*next;
	int		delete_flag;

	current = *lst;
	while (current)
	{
		delete_flag = 0;
		next = current->next;
		if (current->wildcard)
			ft_expand_wildcard(current, &delete_flag);
		if (delete_flag)
		{
			if (*lst == current)
			{
				*lst = current->next;
				data->b_tree->token = current->next;
			}
			if (current->next)
				current->next->prev = current->prev;
			if (current->prev)
				current->prev->next = current->next;
			free(current->content);
			free(current);
		}
		current = next;
	}
}
