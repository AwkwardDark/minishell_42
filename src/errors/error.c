/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:59:36 by pierre            #+#    #+#             */
/*   Updated: 2024/09/04 23:52:58 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* concatenate cmd and error_messsage and adds a \n (Without any Malloc) */
void	error_disp(char *cmd, char *error_message)
{
	char	buffer[500];
	int		cmd_len;
	int		error_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error_message);
	ft_memcpy(buffer, cmd, cmd_len);
	ft_memcpy(buffer + cmd_len, error_message, error_len);
	ft_memcpy(buffer + cmd_len + error_len, "\n", 1);
	buffer[cmd_len + error_len + 2] = 0;
	write(STDERR_FILENO, buffer, error_len + cmd_len + 1);
}

/* concatenate cmd and error_messsage and adds a \n 
(Without any Malloc) and exits */
void	error_disp_exit(char *cmd, char *error_message, int eno)
{
	char	buffer[500];
	int		cmd_len;
	int		error_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error_message);
	ft_memcpy(buffer, cmd, cmd_len);
	ft_memcpy(buffer + cmd_len, error_message, error_len);
	ft_memcpy(buffer + cmd_len + error_len, "\n", 1);
	buffer[cmd_len + error_len + 2] = 0;
	write(STDERR_FILENO, buffer, error_len + cmd_len + 1);
	exit(eno);
}
