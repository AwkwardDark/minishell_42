/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:22:54 by pierre            #+#    #+#             */
/*   Updated: 2024/09/19 22:34:43 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	n;

	n = 0;
	if (!s)
		return (0);
	while (s[n])
	{
		if (ft_putchar_fd(s[n], fd) < 0)
			return (-1);
		n++;
	}
	return (0);
}
