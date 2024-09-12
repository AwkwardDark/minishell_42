/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:15:15 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/11 18:47:58 by pbeyloun         ###   ########.fr       */
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

void	child_sigint(int code)
{
	exit(128 + code);
}

void	parenthandler(int code)
{
	(void)code;
	write(1, "\n", 1);
}