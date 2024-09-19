/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/19 20:37:46 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static int	main_loop(t_data *data)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, main_sigint);
	data->input = readline(GREEN GRAS "minishell ~" RESET);
	data->exit_status = 0;
	if (!data->input)
	{
		printf("exit\n");
		return (-1);
	}
	add_history(data->input);
	if (data->input[0] != '\0' && ft_parser(data->input, data))
	{
		data->b_tree = create_tokentree(&data->token_lst);
		data->bin->tree = data->b_tree;
		exec_btree(data->b_tree, data);
		data->lst_exit_status = data->exit_status;
		clr_btree(data->b_tree);
		data->token_lst = NULL;
	}
	else
		ft_free_lst(&data->token_lst);
	free(data->input);
	data->input = NULL;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argv;
	if (argc != 1)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error(7), 1);
	ft_memset(data, 0, sizeof(t_data));
	if (ft_init_data(envp, data))
		return (1);
	while (1)
	{
		if (main_loop(data) == -1)
			break ;
	}
	ft_free_exit(data);
	return (0);
}

		/* signal(SIGQUIT, SIG_IGN);
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
		data->input = NULL; */