/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_gb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:42:53 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/20 00:10:05 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// close all filedescriptors only if they are open
void	close_fds(t_gbcolector *bin)
{
	int			i;
	struct stat	buf;

	i = 0;
	while (i < 1000 && bin->fds[i] != -1)
	{
		if (!fstat(bin->fds[i], &buf))
			close(bin->fds[i]);
		bin->fds[i] = -1;
		i++;
	}
}

// clears the garabage colector
void	clr_gb(t_gbcolector *bin)
{
	close_fds(bin);
	clr_btree(bin->tree);
}

void	free_process(t_data *data)
{
	clr_gb(data->bin);
	ft_free_exit(data);
}
