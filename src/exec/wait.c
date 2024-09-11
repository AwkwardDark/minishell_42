/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:50:24 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/11 13:49:07 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* waits for all children */
void	wait_children(pid_t last_child, t_data *data)
{
	int	status;
	// int	retcode;

	if (last_child < 0)
	{
		data->exit_status = 128 + g_signal;
		return ;
	}
	while (ECHILD != errno)
	{
		if (waitpid(0, &status, 0) == last_child)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else
			{
				g_signal = WTERMSIG(status);
				data->exit_status = 128 + g_signal;
			}
		}
	}
}

// waits for one process SIMPLE_COMMAND
void	simplecmd_wait(int pid, t_data *data)
{
	int	status;
	// int retcode;

	if (pid < 0)
		data->exit_status = g_signal + 128;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else
	{
		g_signal = WTERMSIG(status);
		data->exit_status = g_signal + 128;
	}
	// return (retcode);
}
