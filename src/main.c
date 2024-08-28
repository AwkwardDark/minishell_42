/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/28 16:24:34 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void)argc;
	(void)argv;
	if (ft_init_data(envp, &data))
		return (1);
	while (1)
	{
		data.input = readline(GREEN GRAS "minishell ~" RESET);
		if (!data.input)
			break ;
		ft_parser(data.input, &data);
		// if (ft_execfsaf)
		// 	break ;
		free(data.input);
	}
	ft_free_exit(&data);
	return (0);
}
