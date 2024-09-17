/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:47:04 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/17 12:08:06 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr_fd(token->content, fd);
		ft_putstr_fd(" ", fd);
		token = token->next;
	}
	if (newline)
		ft_putstr_fd("\n", fd);
	data->exit_status = 0;
}
