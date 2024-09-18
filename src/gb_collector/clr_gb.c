/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_gb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:42:53 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/18 15:18:13 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_gbcolector *bin)
{
	int	i;
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
