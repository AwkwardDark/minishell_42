/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/27 11:57:51 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*buffer;
	
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		buffer = readline(GREEN "minishell~" RESET);
		//ft_parser(buffer);
	}
	return (0);
}
