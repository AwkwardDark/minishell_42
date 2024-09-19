/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/19 15:18:24 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_btree	*tree;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(7), 1);
	ft_memset(data, 0, sizeof(t_data));
	if (ft_init_data(envp, data))
		return (1);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, main_sigint);
		data->input = readline(GREEN GRAS "minishell ~" RESET);
		data->exit_status = 0;
		if (!data->input)
		{
			printf("exit\n");
			break ;
		}
		add_history(data->input);
		if (data->input[0] != '\0' && ft_parser(data->input, data))
		{
			tree = create_tokentree(&data->token_lst);
			data->bin->tree = tree;
			data->b_tree = tree;
			exec_btree(tree, data);
			data->lst_exit_status = data->exit_status;
			clr_btree(tree);
			data->token_lst = NULL;
		}
		else
			ft_free_lst(&data->token_lst);
		free(data->input);
		data->input = NULL;
	}
	ft_free_exit(data);
	return (0);
}
