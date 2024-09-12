/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:15:15 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/12 18:27:04 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_main(int code)
{
	(void)code;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_signal == 0)
		rl_redisplay();
}

void	heredoc_handler(int code)
{
	g_signal = code;
	close(0);
}

void	child_sigint(int code)
{
	exit(128 + code);
}

void	here_docsignals(t_data *data)
{
	if (signal(SIGINT, heredoc_handler) == SIG_ERR)
		ft_putstr_fd("error in signal function on SIGINT handler", 2);
}

void	sigint_exit(t_data *data)
{
	if (g_signal != 0)
	{
		clr_gb(data->bin);
		ft_free_exit(data);
		exit(128 + g_signal);
	}
}

void	parenthandler(int code)
{
	(void)code;
	write(1, "\n", 1);
}