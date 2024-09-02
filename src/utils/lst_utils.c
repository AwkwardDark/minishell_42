/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:14:57 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/02 18:10:16 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_free_lst(t_token **a)
{
	t_token	*temp;

	while (*a)
	{
		temp = (*a)->next;
		free((*a)->content);
		free(*a);
		*a = temp;
	}
}

t_token	*ft_lstnew(char *content)
{
	t_token		*lstnew;

	lstnew = malloc(sizeof(t_token));
	if (!lstnew)
		return (NULL);
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

void ft_print_lst(t_token *lst)
{
    t_token *current = lst;
	int		i = 0;
    
	while (current != NULL)
	{
        printf("n%d -> %s ~~~~", i, current->content);
		printf(" token -> %d\n", current->token_type);
        current = current->next;
		i++;
    }
}
