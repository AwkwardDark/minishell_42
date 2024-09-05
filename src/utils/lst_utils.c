/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:14:57 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/05 15:58:56 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It frees the content of each node and the node itself*/
void	ft_free_lst(t_token **lst)
{
	t_token	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

t_token	*ft_lstnew(char *content)
{
	t_token		*lstnew;

	lstnew = malloc(sizeof(t_token));
	if (!lstnew)
		return (NULL);
	ft_memset(lstnew, 0, sizeof(t_token));//inutile?
	lstnew->content = content;
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

void	ft_print_lst(t_token *lst)
{
	int		i;
	t_token	*current;

	i = 0;
	current = lst;
	while (current)
	{
		if ((current->token_type == R_IN) || (current->token_type == R_OUT) || \
			(current->token_type == HEREDOC) || (current->token_type == APPEND))
			printf("\n");
		printf("n%d -> %s ----", i, current->content);
		printf(" token -> %d\n", current->token_type);
		if (current->redir)
			printf(" ~~~ redir file -> %s ~~~\n\n", current->redir);
		current = current->next;
		i++;
	}
}
