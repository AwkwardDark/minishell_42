/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:21 by pierre            #+#    #+#             */
/*   Updated: 2024/05/03 13:49:12 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	index_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base, int base_len)
{
	int	nbr;
	int	i;
	int	idx;
	int	is_neg;

	nbr = 0;
	i = 0;
	idx = 0;
	if (str[0] == '-')
		is_neg = -1;
	else
		is_neg = 1;
	while (str[i])
	{
		idx = index_in_base(str[i], base);
		if (idx == -1)
			break ;
		nbr = (nbr * base_len) + idx;
		i++;
	}
	return (nbr * is_neg);
}
