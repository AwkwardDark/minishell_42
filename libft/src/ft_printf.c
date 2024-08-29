/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:02:51 by pierre            #+#    #+#             */
/*   Updated: 2024/06/03 16:28:56 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	valist;
	int		ret;

	ret = 0;
	if (!str)
		return (-1);
	va_start(valist, str);
	if (str)
		ret = displayer(str, valist);
	va_end(valist);
	return (ret);
}

int	displayer(const char *str, va_list valist)
{
	int		i;
	int		ret;
	t_disp	format;

	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			format = init_disp(&str[i]);
			ret = displayer_aux(ret, valist, format);
			i += next_disp(&str[i]);
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			ret++;
			i++;
		}
	}
	return (ret);
}

int	displayer_aux(int n, va_list valist, t_disp data)
{
	if (data.format == '%')
	{
		ft_putchar_fd('%', 1);
		n++;
	}
	else
		n += disp_formats(valist, data);
	return (n);
}

int	disp_formats(va_list valist, t_disp frm)
{
	long	temp;

	if (frm.format == 'c')
		return (format_c(va_arg(valist, int), frm));
	else if (frm.format == 's')
		return (format_s(va_arg(valist, char *), frm));
	else if (frm.format == 'p')
		return (format_p(va_arg(valist, void *), frm));
	else if (frm.format == 'd' || frm.format == 'i')
	{
		temp = va_arg(valist, int);
		if (temp < 0)
			return (format_d_i(temp * -1, frm, 1));
		return (format_d_i(temp, frm, 0));
	}
	else if (frm.format == 'u')
		return (format_u(va_arg(valist, long), frm));
	else if (frm.format == 'x' || frm.format == 'X')
		return (format_x((unsigned long)va_arg(valist, unsigned long),
				frm.format, frm));
	return (0);
}

int	format_c(char c, t_disp data)
{
	int	padding;
	int	ret;

	ret = 0;
	padding = data.precision - 1;
	if (padding > 0 && is_match(data.flag, "0."))
		ret = disp_padding(data, padding, 0);
	ft_putchar_fd(c, 1);
	if (padding > 0 && data.flag == '-')
		ret = disp_padding(data, padding, 0);
	return (1 + ret);
}
