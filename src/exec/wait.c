/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:50:24 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/10 12:03:15 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* waits for all children */
int	wait_children(pid_t last_child)
{
	int	status;
	int	retcode;

	while (ECHILD != errno)
	{
		if (waitpid(0, &status, 0) == last_child)
		{
			if (WIFEXITED(status))
				retcode = WEXITSTATUS(status);
			else
			{
				printf("here");
				retcode = WSTOPSIG(status);
			}
		}
	}
	return (retcode);
}

// waits for one process SIMPLE_COMMAND
int	simplecmd_wait(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}
