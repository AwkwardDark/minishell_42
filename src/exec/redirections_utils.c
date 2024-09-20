/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:43:46 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/20 15:28:37 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*When we redirect to a wildcard, if its expand to more than 1 file, it will
create an error (ambiguous redirect). So we have to treat the wildcard
expansion differently in this scenario*/
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
