/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 02:01:10 by pierre            #+#    #+#             */
/*   Updated: 2024/06/03 16:28:50 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	format_u(long l, t_disp data)
{
	unsigned int	u;
	int				padding;

	u = (unsigned int)l;
	padding = data.precision - numb_len(u, 10);
	if (padding < 0)
		padding = 0;
	if (is_match(data.flag, ".0") && padding > 0)
		disp_padding(data, padding, 0);
	ft_putnbr_fd(u, 1);
	if (data.flag == '-' && padding > 0)
		disp_padding(data, padding, 0);
	return (numb_len(u, 10) + padding);
}

int	format_p(void *p, t_disp data)
{
	int		padding;

	padding = data.precision - (numb_len_ul((unsigned long)p, 16) + 2);
	if (padding < 0)
		padding = 0;
	if (!p)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	if (is_match(data.flag, ".0") && padding > 0)
		disp_padding(data, padding, 0);
	to_hex((unsigned long)p, &ft_tolower);
	if (data.flag == '-' && padding > 0)
		disp_padding(data, padding, 0);
	return (2 + numb_len_ul((unsigned long)p, 16) + padding);
}

int	format_d_i(long nbr, t_disp data, int is_neg)
{
	int	padding;
	int	ret;

	ret = 0;
	padding = data.precision - numb_len(nbr, 10);
	if (is_match(data.flag, "0.") && padding > 0)
		ret = disp_padding(data, padding, is_neg);
	else if (is_neg)
		ft_putchar_fd('-', 1);
	ft_putnbr_fd(nbr, 1);
	if (data.flag == '-' && padding > 0)
		ret = disp_padding(data, padding, is_neg);
	return (numb_len(nbr, 10) + ret + is_neg);
}

int	format_s(char *str, t_disp data)
{
	int	padding;
	int	ret;

	ret = 0;
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	padding = data.precision - ft_strlen(str);
	if (data.flag == 0 && padding > 0)
		ret = disp_space(padding);
	else if (data.flag == '.' && (int)ft_strlen(str) > data.precision)
	{
		disp_str_n(str, data.precision);
		return (data.precision);
	}
	if (data.flag == '0')
		ret = disp_space(padding);
	ft_putstr_fd(str, 1);
	if (data.flag == '-')
		ret = disp_space(padding);
	return (ft_strlen(str) + ret);
}

int	format_x(long u, int c, t_disp data)
{
	unsigned int	x;
	int				padding;
	int				ret;

	x = (unsigned int)u;
	ret = 0;
	padding = data.precision - numb_len(x, 16);
	if (padding > 0 && is_match(data.flag, "0."))
		ret = disp_padding(data, padding, 0);
	if (c == 'X')
		to_hex(x, &ft_toupper);
	else
		to_hex(x, &ft_tolower);
	if (padding > 0 && data.flag == '-')
		ret = disp_padding(data, padding, 0);
	return (numb_len(x, 16) + ret);
}
