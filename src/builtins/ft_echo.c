/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:47:04 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/23 16:24:48 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*get_disptoken(t_token *token)
{
	while (token != NULL)
	{
		if (token->token_type == WORD && ft_strncmp(token->content, "-n", 2)
			!= 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

/*
	goes through the token list searching for the first token_type
	word and checking if its its equal to -n
*/
static int	get_nflag(t_token *token)
{
	while (token != NULL)
	{
		if (token->token_type == WORD)
		{
			if (!ft_strncmp(token->content, "-n", 2))
				return (1);
			return (0);
		}
		token = token->next;
	}
	return (0);
}

/*
	goes through the token list checking if there are no next token_type WORD
*/
static int	display_space(t_token *token)
{
	while (token != NULL)
	{
		if (token->token_type == WORD)
			return (1);
		token = token->next;
	}
	return (0);
}

// handles echo builtin with the flag -n
void	ft_echo(t_token *token, int fd, t_data *data)
{
	int	newline;

	newline = 1;
	if (get_nflag(token))
	{
		newline = 0;
		token = get_disptoken(token);
	}
	while (token != NULL)
	{
		if (token->token_type == WORD && ft_putstr2(token->content, fd) < 0)
		{
			data->exit_status = 1;
			return ;
		}
		if (token->token_type == WORD && display_space(token->next))
			ft_putstr2(" ", fd);
		token = token->next;
	}
	if (newline)
		ft_putstr2("\n", fd);
	data->exit_status = 0;
}
