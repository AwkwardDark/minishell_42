/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:57:03 by pierre            #+#    #+#             */
/*   Updated: 2024/09/22 20:18:24 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if the command is a builtin
int	ft_is_builtins(t_token *token)
{
	if (!token)
		return (0);
	while (token != NULL && token->token_type != WORD)
		token = token->next;
	if (token == NULL)
		return (0);
	if (!ft_strcmp("echo", token->content)
		|| !ft_strcmp("export", token->content)
		|| !ft_strcmp("exit", token->content)
		|| !ft_strcmp("pwd", token->content)
		|| !ft_strcmp("env", token->content)
		|| !ft_strcmp("unset", token->content)
		|| !ft_strcmp("cd", token->content))
		return (1);
	return (0);
}
