/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:42:44 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/17 01:40:48 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errorcmd_failed(char *cmd, char *error)
{
	char	buffer[500];
	int		error_len;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error);
	ft_memcpy(buffer, "minishell: ", 11);
	ft_memcpy(buffer + 11, cmd, cmd_len);
	ft_memcpy(buffer + 11 + cmd_len, ": ", 2);
	ft_memcpy(buffer + 11 + cmd_len + 2, error, error_len);
	buffer[11 + cmd_len + 2 + error_len] = 0;
	ft_putstr_fd(buffer, 2);
}
