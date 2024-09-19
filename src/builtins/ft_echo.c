/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:47:04 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/19 23:57:07 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handles echo builtin with the flag -n
void	ft_echo(t_token *token, int fd, t_data *data)
{
	int	newline;

	newline = 1;
	if (token != NULL && token->token_type == WORD
		&& !ft_strcmp(token->content, "-n"))
	{
		newline = 0;
		token = token->next;
	}
	while (token != NULL && token->token_type == WORD)
	{
		ft_putstr2(token->content, fd);
		if (token->next != NULL && token->next->token_type == WORD)
			ft_putstr2(" ", fd);
		token = token->next;
	}
	if (newline)
		ft_putstr2("\n", fd);
	data->exit_status = 0;
}
