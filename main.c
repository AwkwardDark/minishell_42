/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/17 12:35:57 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

int main(int argc, char **argv, char **envp)
{
	t_data *data;
	t_btree *tree;
	
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
		data->input = readline(GREEN GRAS "minishell ~" RESET);
		if (!data->input)
		{
			printf("exit\n");
			break ;
		}
		add_history(data->input);
		if (data->input[0] != '\0' && ft_parser(data->input, data))
		{
			tree = create_tokentree(&data->token_lst);
			exec_btree(tree, data);
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


