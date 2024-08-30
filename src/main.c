/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/08/30 16:13:09 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data	*data;
	
	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(2), 1);
	printf("yoyo");
	if (ft_init_data(envp, data))
		return (1);
	while (1)
	{
		data->input = readline(GREEN GRAS "minishell ~" RESET);
		if (!data->input)
			break ;
		add_history(data->input);
		ft_parser(data->input, data);
		free(data->input);
	}
	ft_print_lst(data->token_lst);
	ft_free_exit(data);
	return (0);
}
