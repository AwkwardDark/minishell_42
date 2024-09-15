/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childp_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:15:15 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/16 01:11:37 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_sigint(int code)
{
	exit(128 + code);
}

void	here_docsignals(t_data *data)
{
	if (signal(SIGINT, heredoc_handler) == SIG_ERR)
		ft_putstr_fd("error in signal function on SIGINT handler", 2);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("error in signal function on SIGQUIT handler", 2);
}

void	heredoc_handler(int code)
{
	g_signal = code;
	rl_done = 1;
	close(0);
}

void	sigint_exit(t_data *data)
{
	if (g_signal != 0)
	{
		rl_done = 0;
		free_process(data);
		exit(128 + g_signal);
	}
}

void	child_sigquit(int code)
{
	write(1, "\n", 1);
	rl_redisplay();
	exit(128 + code);
}
