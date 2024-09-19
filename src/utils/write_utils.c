/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 22:29:42 by pierre            #+#    #+#             */
/*   Updated: 2024/09/19 23:50:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr2(char *str, int fd)
{
	if (ft_putstr_fd(str, fd) < 0)
		ft_putstr_fd("minishell: write error: No space left on device", 2);
}
