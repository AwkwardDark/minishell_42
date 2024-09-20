/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:14:57 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/20 14:43:06 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It frees the content of each node, redirections and the node itself*/
void	ft_free_lst(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		if ((*lst)->content)
			free((*lst)->content);
		if ((*lst)->redir)
			free((*lst)->redir);
		if ((*lst)->old_redir)
			free((*lst)->old_redir);
		free(*lst);
		*lst = temp;
	}
}

/*Creates a node and initialises all the token struct elements*/
t_token	*ft_lstnew(char *content)
{
	t_token	*lstnew;

	lstnew = malloc(sizeof(t_token));
	if (!lstnew)
		return (NULL);
	ft_memset(lstnew, 0, sizeof(t_token));
	lstnew->redir = NULL;
	lstnew->content = content;
	lstnew->del_wild_flag = 0;
	lstnew->next = NULL;
	lstnew->prev = NULL;
	return (lstnew);
}

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*current;

	current = lst;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

/*Adds a new node at the end of the double linnked list*/
void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
	new->prev = last;
}

void	ft_insert_after(t_token *current, t_token *new)
{
	new->next = current->next;
	new->prev = current;
	if (current->next)
		current->next->prev = new;
	current->next = new;
}
