/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:43:46 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/20 12:57:19 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_wildcard(t_token *current)
{
	struct dirent	*entry;
	DIR				*dirp;
	char			*temp;
	int				i;

	i = 0;
	dirp = opendir(".");
	entry = readdir(dirp);
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			if (ft_wild_match(entry->d_name, current->redir))
			{
				i++;
				if (i > 1)
				{
					current->del_wild_flag = 1;
					break ;
				}
				temp = entry->d_name;
			}
		}
		entry = readdir(dirp);
	}
	if (i == 1)
	{
		free(current->redir);
		current->redir = ft_strdup(temp);
	}
	closedir(dirp);
}
