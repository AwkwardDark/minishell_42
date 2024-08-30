/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:33:34 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/30 18:40:56 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_token **a)
{
	t_token	*temp;

	while (*a)
	{
		temp = (*a)->next;
		free(*a);
		*a = temp;
	}
}

t_token	*ft_lstnew(char *content, t_type type)
{
	t_token		*lstnew;

	lstnew = malloc(sizeof(t_token));
	if (!lstnew)
		return (NULL);
	lstnew->content = content;
	lstnew->next = NULL;
	lstnew->prev = NULL;
	if (!type)
		lstnew->token_type = NULL;
	else
		lstnew->token_type = type;
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

void ft_print_lst(t_token *lst)
{
    t_token *current = lst;
	int		i = 0;
    
	while (current != NULL) {
        printf("n%d -> %s\n", i, current->content);
        current = current->next;
		i++;
    }
}