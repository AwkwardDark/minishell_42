/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:02:45 by pierre            #+#    #+#             */
/*   Updated: 2024/07/23 10:49:38 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	is_match(char c, char *match)
{
	while (*match)
	{
		if (*match == c)
			return (1);
		match++;
	}
	return (0);
}

void	to_hex(unsigned long nbr, int (*f)(int))
{
	char	*hex;

	hex = "0123456789abcdef";
	if (nbr / 16 == 0)
		ft_putchar_fd(f(hex[nbr]), 1);
	else
	{
		to_hex(nbr / 16, f);
		ft_putchar_fd(f(hex[nbr % 16]), 1);
	}
}

int	numb_len_ul(unsigned long num, int base)
{
	int	n;

	n = 0;
	while (num / base != 0)
	{
		num = num / base;
		n++;
	}
	n++;
	return (n);
}

int	numb_len(long num, int base)
{
	int	n;

	n = 0;
	if (num < 0)
		n++;
	while (num / base != 0)
	{
		num = num / base;
		n++;
	}
	n++;
	return (n);
}

int	disp_str_n(char *str, int precision)
{
	int	n;

	n = 0;
	while (n < precision)
	{
		ft_putchar_fd(str[n], 1);
		n++;
	}
	return (precision);
}
