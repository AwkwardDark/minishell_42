/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:30:59 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/05 16:56:26 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_btree *btree;

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
		data->input = readline(GREEN GRAS "minishell ~" RESET);
		if (!data->input || !ft_strcmp(data->input, "exit"))
			break ;
		add_history(data->input);
		ft_parser(data->input, data);
		ft_print_lst(data->token_lst);
		// fprintf(stderr, "************************** \n");
		btree = create_tokentree(&data->token_lst);
		// display_btree(btree);
		exec_btree(btree, data->env);
		// clr_btree(btree);
		data->token_lst = NULL;
		// free(data->input);
		// ft_free_lst(&data->token_lst);
		rl_on_new_line();
	}
	ft_free_exit(data);
	return (0);
}
