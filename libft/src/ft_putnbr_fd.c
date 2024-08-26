/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:22:47 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:30:50 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(long n, int fd)
{
	long	temp;

	if (n / 10 == 0)
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *= -1;
		}
		ft_putchar_fd(n + '0', fd);
	}
	else
	{
		temp = (long)n;
		if (n < 0)
			temp *= -1;
		else
			temp = n;
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((temp % 10) + '0', fd);
	}
}
