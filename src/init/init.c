/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:35:25 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/06 15:26:03 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	data->quote_type = '\0';
	data->token_lst = NULL;//we can ignore this initialisation?
	return (0);
}
