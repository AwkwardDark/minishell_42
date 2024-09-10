/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:15:15 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/10 12:11:52 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_slash(int code)
{
	(void)code;
	// rl_on_new_line();
	rl_redisplay();
}

void	handler_c(int code)
{
	(void )code;
	exit(0);
}

void	handler_main(int code)
{
	(void)code;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_signal == 0)
		rl_redisplay();
}
