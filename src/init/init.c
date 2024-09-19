/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:35:25 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/19 15:33:37 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_gb(t_data *data)
{
	int	i;

	i = 0;
	while (i < 1000)
	{
		data->bin->fds[i] = -1;
		i++;
	}
	data->bin->tree = NULL;
}

/*It verifies if envp exits, creates a copy in a linked list for an easier
manipulation with expand, export and unset. It also initialises the elements of
the data struct and garbage collector struct*/
int	ft_init_data(char **envp, t_data *data)
{
	data->env = ft_cpyenv(envp);
	data->export = ft_cpyenv(envp);
	if (!data->env || !data->export)
		return (ft_error(6), 1);
	data->free_flag = 0;
	data->exit_status = 0;
	data->quote_type = '0';
	data->symbol = '\0';
	data->lst_exit_status = 0;
	data->heredoc_flag = 0;
	data->token_lst = NULL;
	data->bin = (struct s_garbagecolector *)malloc(sizeof(t_gbcolector));
	if (!data->bin)
		return (-1);
	init_gb(data);
	return (0);
}
