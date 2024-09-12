/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:57:07 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/12 15:37:35 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple_wildcard(t_token *current, int *flag)
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
			*flag = 1;
			ft_insert_after(current, ft_lstnew(ft_strdup(entry->d_name)));
		}
		entry = readdir(dirp);
	}
	closedir(dirp);
}

void	ft_wildcard(t_token **lst, t_data *data)
{
	t_token	*current;
	t_token *next;
	int		delete_flag;
	
	current = *lst;
	while(current)
	{
		delete_flag = 0;
		next = current->next;
		if ((current->wildcard)/*&& ft_valid_wildcard(current)*/)
			ft_simple_wildcard(current, &delete_flag);
		if (delete_flag)
		{
			if (*lst == current)
			{
				*lst = current->next;
				data->token_lst = current->next;
			}
			if (current->next)
				current->next->prev = current->prev;
			if (current->prev)
				current->prev->next = current->next;
			free(current);
		}
		current = next;
	}
}
