/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/17 00:12:42 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_btree *tree;
	char	*pwd;
	(void)argc;
	(void)argv;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(7), 1);
	ft_memset(data, 0, sizeof(t_data));
	char **arg;
	if (ft_init_data(envp, data))
		return (1);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, main_sigint);
		g_signal = 0;
		data->input = readline("minishell ~ ");
		if (!data->input)
		{
			printf("exit\n");
			break ;
		}
		add_history(data->input);
		ft_parser(data->input, data);
		tree = create_tokentree(&data->token_lst);
		data->bin->tree = tree;
		exec_btree(tree, data);
		fprintf(stderr, "exit status: %d\n", data->exit_status);
		clr_btree(tree);
		data->token_lst = NULL;
		free(data->input);
		data->input = NULL;
	}
	ft_free_exit(data);
	return (0);
}


