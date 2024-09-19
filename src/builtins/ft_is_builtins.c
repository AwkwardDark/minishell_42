/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:57:03 by pierre            #+#    #+#             */
/*   Updated: 2024/09/20 00:03:03 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks if the command is a builtin
int	ft_is_builtins(char *cmd)
{
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("exit", cmd) || !ft_strcmp("pwd", cmd)
		|| !ft_strcmp("env", cmd) || !ft_strcmp("unset", cmd)
		|| !ft_strcmp("cd", cmd))
		return (1);
	return (0);
}
