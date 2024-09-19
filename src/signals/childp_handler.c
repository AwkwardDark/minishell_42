/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childp_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:15:15 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/20 00:13:05 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// child process exits in case of ctrl+c
void	child_sigint(int code)
{
	exit(128 + code);
}

// setsup signals for the heredoc
void	here_docsignals(void)
{
	if (signal(SIGINT, heredoc_handler) == SIG_ERR)
		ft_putstr2("error in signal function on SIGINT handler", 2);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_putstr2("error in signal function on SIGQUIT handler", 2);
}

// sigint signal for heredoc
void	heredoc_handler(int code)
{
	g_signal = code;
	rl_done = 1;
	close(0);
}

/*
	checks if the the signal was interupted adn frees data and exits
*/
void	sigint_exit(t_data *data)
{
	if (g_signal != 0)
	{
		rl_done = 0;
		free_process(data);
		exit(128 + g_signal);
	}
}

// handles ctrl + '\'
void	child_sigquit(int code)
{
	write(1, "\n", 1);
	rl_redisplay();
	exit(128 + code);
}
