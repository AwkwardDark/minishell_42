/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:44:21 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/19 16:00:46 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_execve(char *path, char **argv, char **env_arr)
{
	free(path);
	clear_wordar(argv);
	clear_wordar(env_arr);
	exit(EXIT_FAILURE);
}

int	free_exec_pipe(t_data *data)
{
	data->lst_exit_status = 1;
	error_disp_exit(strerror(errno), "pipe", -1);
	return (-1);
}

int	free_exec_fork(t_data *data)
{
	close_fds(data->bin);
	data->exit_status = 1;
	error_disp_exit(strerror(errno), "fork", 1);
	return (-1);
}

int	free_exec_dup2(t_data *data)
{
	close_fds(data->bin);
	data->exit_status = 1;
	error_disp_exit(strerror(errno), "dup2", 1);
	return (-1);
}
