/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 22:57:03 by pierre            #+#    #+#             */
/*   Updated: 2024/09/16 17:37:32 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtins(char *cmd)
{
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("exit", cmd) || !ft_strcmp("pwd", cmd)
		|| !ft_strcmp("env", cmd) || !ft_strcmp("unset", cmd)
		|| !ft_strcmp("cd", cmd))
		return (1);
	return (0);
}
