/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:50:24 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/17 12:21:04 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* waits for all children */
void	wait_children(pid_t last_child, t_data *data)
{
	int	status;

	if (last_child < 0)
		return ;
	while (ECHILD != errno)
	{
		if (waitpid(0, &status, 0) == last_child)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			if (data->exit_status > 128)
				g_signal = 2;
			else
				g_signal = 0;
		}
	}
}

// waits for one process SIMPLE_COMMAND
void	simplecmd_wait(int pid, t_data *data)
{
	int	status;

	if (pid < 0)
		return ;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	if (data->exit_status > 128)
	{
		if (data->exit_status > 128)
			g_signal = 2;
		else
			g_signal = 0;
	}
}
