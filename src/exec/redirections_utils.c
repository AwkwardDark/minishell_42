/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:43:46 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/20 17:29:59 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_redirout(t_token *token, int *fd)
{
	if (token->wildcard)
		ft_redir_wildcard(token, fd);
	if (token->token_type == R_OUT && token->del_wild_flag == 0)
		*fd = open(token->redir, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else if (token->token_type == APPEND && token->del_wild_flag == 0)
		*fd = open(token->redir, O_CREAT | O_WRONLY | O_APPEND, 0664);
}

void	ft_ambiguous_redirect(t_token *token)
{
	ft_putstr_fd("minishell: ", 2);
	if (token->redir[0] == '\0')
		ft_putstr_fd(token->old_redir, 2);
	else
		ft_putstr_fd(token->redir, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

/*If there are more than 1 entry on the directory, it should not redirect*/
static int	ft_check_nb_entry(int i, t_token *current, int *fd)
{
	if (i > 1)
	{
		current->del_wild_flag = 1;
		*fd = -1;
		return (1);
	}
	return (0);
}

/*It there's only 1 match with the wildcard, we create the new string to which
it will redirect*/
static void	ft_replace_expanded(int i, char *temp, t_token *current)
{
	if (i == 1)
	{
		free(current->redir);
		current->redir = ft_strdup(temp);
	}
}

/*When we redirect to a wildcard, if its expand to more than 1 file, it will
create an error (ambiguous redirect). So we have to treat the wildcard
expansion differently in this scenario*/
void	ft_redir_wildcard(t_token *current, int *fd)
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
				if (ft_check_nb_entry(i, current, fd))
					break ;
				temp = entry->d_name;
			}
		}
		entry = readdir(dirp);
	}
	ft_replace_expanded(i, temp, current);
	closedir(dirp);
}
