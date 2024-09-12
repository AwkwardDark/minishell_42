/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:35:25 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/12 14:58:22 by pbeyloun         ###   ########.fr       */
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
manipulation with expand, export and unset. It also initialise the elements of
data struct*/
int	ft_init_data(char **envp, t_data *data)
{
	if (!envp || !envp[0])
		data->env = NULL;
	else
	{
		data->env = ft_cpyenv(envp);
		if (!data->env)
			return (ft_error(6), 1);
	}
	data->exit_status = 0;
	data->quote_type = '0';
	data->token_lst = NULL;//we can ignore this initialisation?
	data->bin = (struct s_garbagecolector*)malloc(sizeof(t_gbcolector));
	if (!data->bin)
		return (-1);
	init_gb(data);
	return (0);
}
