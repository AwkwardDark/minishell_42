/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_gb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:42:53 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/12 16:41:42 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clr_gb(t_gbcolector *bin)
{
	int i;

	i = 0;
	while (i < 1000 && bin->fds[i] != -1)
	{
		close(bin->fds[i]);
		i++;
	}
	// fprintf(stderr, "beginning to free\n");
	clr_btree(bin->tree);
}