/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:33:34 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/02 14:41:23 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_token **a)
{
	t_token	*next;
	t_token	*cur;

	cur = *a;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	*a = NULL;
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
		lstnew->token_type = 0;
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

/* prints the list of tokens */
void	ft_print_lst(t_token *lst)
{
	t_token	*current;
	int		i;

	i = 0;
	current = lst;
	while (current != NULL)
	{
		printf("n%d -> %s\n", i, current->content);
		current = current->next;
		i++;
	}
}

/* switch case to display all the enumerated types */
void	display_type(t_type type)
{
	switch (type)
	{
	case PIPE:
		printf(" | ");
		break;
	case OR:
		printf(" || ");
		break;
	case AND:
		printf(" && ");
		break;
	default:
		printf(" cmd ");
		break;
	}
}