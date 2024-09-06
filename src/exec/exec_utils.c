/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:29:03 by pierre            #+#    #+#             */
/*   Updated: 2024/09/05 17:39:02 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if thes command is a here doc or not
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

// get the limiter
char	*get_limiter(t_token *token)
{
	while (token != NULL)
	{
		if (token->token_type == HEREDOC)
			return (token->redir);
		token = token->next;
	}
	return (NULL);
}
