/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:29:42 by pierre            #+#    #+#             */
/*   Updated: 2024/09/20 09:32:49 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putstr2(char *str, int fd)
{
	if (ft_putstr_fd(str, fd) < 0)
	{
		ft_putstr_fd("minishell: write error: No space left on device\n", 2);
		return (-1);
	}
	return (0);
}
