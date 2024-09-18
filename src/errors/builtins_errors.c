/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:42:44 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/18 23:44:40 by pierre           ###   ########.fr       */
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

void	errorcmd_failed2(char *cmd, char *arg, char *error)
{
	char	buffer[500];
	int		arg_len;
	int		error_len;
	int		cmd_len;

	arg_len = ft_strlen(arg);
	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error);
	ft_memcpy(buffer, "minishell: ", 11);
	ft_memcpy(buffer + 11, cmd, cmd_len);
	ft_memcpy(buffer + 11 + cmd_len, ": ", 2);
	ft_memcpy(buffer + 11 + cmd_len + 2, arg, arg_len);
	ft_memcpy(buffer + 11 + cmd_len + 2 + arg_len, ": ", 2);
	ft_memcpy(buffer + 11 + cmd_len + 4 + arg_len, error, error_len);
	ft_memcpy(buffer + 11 + cmd_len + 4 + arg_len + error_len, "\n", 1);
	buffer[11 + cmd_len + 4 + error_len + arg_len + 1] = 0;
	ft_putstr_fd(buffer, 2);
}

/*Before exiting the program, it frees the environment list, the prompt input,
and data and bin structures. Also it clears the prompt history*/
void	ft_free_exit(t_data *data)
{
	if (data->env)
		ft_clrenv(&data->env);
	if (data->input)
		free(data->input);
	if (data)
	{
		if (data->bin)
			free(data->bin);
		free(data);
	}
	rl_clear_history();
}
