/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:15:15 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/14 20:19:29 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_sigint(int code)
{
	(void)code;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_signal == 0)
		rl_redisplay();
}

void	main_sigquit(int code)
{
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void	heredoc_handler(int code)
{
	g_signal = code;
	rl_done = 1;
	close(0);
}

void	child_sigint(int code)
{
	exit(128 + code);
}

void	child_sigquit(int code)
{
	write(1, "\n", 1);
	rl_redisplay();
	exit(128 + code);
}

void	here_docsignals(t_data *data)
{
	if (signal(SIGINT, heredoc_handler) == SIG_ERR)
		ft_putstr_fd("error in signal function on SIGINT handler", 2);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("error in signal function on SIGQUIT handler", 2);
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

void	parenthandler(int code)
{
	(void)code;
	write(1, "\n", 1);
}