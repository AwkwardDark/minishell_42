/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:54:06 by pierre            #+#    #+#             */
/*   Updated: 2024/06/03 16:28:46 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	disp_padding(t_disp data, int padding, int is_neg)
{
	int	i;

	i = 0;
	if (is_neg && data.flag != '-')
		ft_putchar_fd('-', 1);
	if (is_match(data.flag, "0-") && is_neg)
		padding--;
	while (i < padding)
	{
		if (is_match(data.flag, "0."))
			ft_putchar_fd('0', 1);
		else if (data.flag == '-')
			ft_putchar_fd(' ', 1);
		i++;
	}
	return (i);
}

int	disp_space(int precision)
{
	int	n;

	n = 0;
	while (n < precision)
	{
		ft_putchar_fd(' ', 1);
		n++;
	}
	return (n);
}

int	get_format(const char *str)
{
	int	i;

	i = 0;
	while (!is_match(str[i], "cspdiuxX%"))
		i++;
	return (i);
}

int	next_disp(const char *str)
{
	int	i;

	i = 0;
	if (is_match(str[i], "cspdiuxX%"))
		return (1);
	while (!is_match(str[i], "cspdiuxX%"))
		i++;
	return (i + 1);
}

t_disp	init_disp(const char *str)
{
	t_disp	data;
	int		i;

	i = 0;
	if (!is_match(str[i], ".-0"))
	{
		data.flag = 0;
		data.precision = ft_atoi(str);
		data.format = str[get_format(str)];
	}
	else
	{
		while (is_match(str[i], ".0-"))
		{
			data.flag = str[i];
			if ((str[i - 1] == '-' && str[i] == '0'))
				data.flag = str[i];
			i++;
		}
		data.precision = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
		data.format = str[i];
	}
	return (data);
}
