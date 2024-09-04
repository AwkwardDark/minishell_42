/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:29:03 by pierre            #+#    #+#             */
/*   Updated: 2024/09/04 10:42:48 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc(t_token *token)
{
	if (!token)
		return (0);
	while (token != NULL)
	{
		if (token->token_type == HEREDOC)
			return (1);
		token = token->next;
	}
	return (0);
}

char *get_limiter(t_token *token)
{
	while (token != NULL)
	{
		if (token->token_type == HEREDOC)
			return (token->content);
		token = token->next;
	}
	return (NULL);
}