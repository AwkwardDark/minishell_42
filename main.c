/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/12 22:08:41 by pierre           ###   ########.fr       */
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
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(7), 1);
	ft_memset(data, 0, sizeof(t_data));
	char **arg;
	if (ft_init_data(envp, data))
		return (1);
	while (1)
	{
		signal(SIGINT, handler_main);
		g_signal = 0;
		data->input = readline(GREEN GRAS "minishell ~" RESET);
		if (!data->input || !ft_strcmp(data->input, "exit") || data->input == NULL)
		{
			printf("exit\n");
			break ;
		}
		add_history(data->input);
		ft_parser(data->input, data);
		tree = create_tokentree(&data->token_lst);
		data->bin->tree = tree;
		exec_btree(tree, data);
		clr_btree(tree);
		data->token_lst = NULL;
		free(data->input);
		data->input = NULL;
	}
	ft_free_exit(data);
	return (0);
}


