/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/11 13:33:06 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_btree *tree;
	(void)argc;
	(void)argv;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_main);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(7), 1);
	ft_memset(data, 0, sizeof(t_data));
	if (ft_init_data(envp, data))
		return (1);
	while (1)
	{
		data->input = readline(GREEN GRAS "minishell ~" RESET);
		g_signal = 0;
		if (!data->input || !ft_strcmp(data->input, "exit"))
			break ;
		add_history(data->input);
		ft_parser(data->input, data);
		tree = create_tokentree(&data->token_lst);
		exec_btree(tree, data);
		clr_btree(tree);
		data->token_lst = NULL;
		free(data->input);
		if (g_signal == 0)
			fprintf(stderr, "exit status: %d\n", data->exit_status);
		else
			fprintf(stderr, "sigexit status: %d\n", data->exit_status);
	}
	ft_free_exit(data);
	return (0);
}


