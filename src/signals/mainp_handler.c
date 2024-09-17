/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainp_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:06:28 by pierre            #+#    #+#             */
/*   Updated: 2024/09/17 14:13:16 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parenthandler(int code)
{
	(void)code;
	write(1, "\n", 1);
}

void	main_sigint(int code)
{
	// (void)code;
	g_signal = code;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	// if (g_signal == 0)
		rl_redisplay();
	// g_signal = code;
}

void	main_sigquit(int code)
{
	// (void)code;
	g_signal = code;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}
