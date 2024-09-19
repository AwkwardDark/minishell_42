/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:14:57 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/19 11:26:40 by pajimene         ###   ########.fr       */
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

void	ft_free_onetoken(t_token *token)
{
	if (!token)
		return ;
	free(token->content);
	free(token);
}

/*Just for visual and debugging purpose*/
// void	ft_print_lst(t_token *lst)
// {
// 	int		i;
// 	t_token	*current;

// 	i = 0;
// 	current = lst;
// 	if (!lst)
// 		return ;
// 	while (current)
// 	{
// 		if ((current->token_type == R_IN) || (current->token_type == R_OUT) || 
//			(current->token_type == HEREDOC) || (current->token_type == APPEND))
// 			printf("\n");
// 		printf("n%d -> %s ----", i, current->content);
// 		printf(" token -> %d\n", current->token_type);
// 		if (current->redir)
// 			printf(" ~~~ redir file -> %s ~~~\n\n", current->redir);
// 		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
// 		current = current->next;
// 		i++;
// 	}
// }
