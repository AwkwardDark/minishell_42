/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:01:54 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/20 00:10:27 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// adds fd the the array of fds
void	add_fdtogb(t_gbcolector *gb, int fd)
{
	int	i;

	i = 0;
	while (gb->fds[i] != -1 && i < 1000)
		i++;
	if (i == 999 && gb->fds[i] != -1)
		ft_putstr2("Too many fds\n", 2);
	else
		gb->fds[i] = fd;
}
