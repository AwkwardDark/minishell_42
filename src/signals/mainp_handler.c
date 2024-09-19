/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainp_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:06:28 by pierre            #+#    #+#             */
/*   Updated: 2024/09/20 00:14:04 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parent handler in execution
void	parenthandler(int code)
{
	(void)code;
	write(1, "\n", 1);
}

// sigint signals parent process
void	main_sigint(int code)
{
	g_signal = code;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// sigquit signal for parent process
void	main_sigquit(int code)
{
	g_signal = code;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}
