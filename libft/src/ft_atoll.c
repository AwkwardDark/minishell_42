/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 21:39:58 by pierre            #+#    #+#             */
/*   Updated: 2024/09/17 22:04:54 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

long long	ft_atoll(const char *nptr)
{
	long long	val;
	int			isneg;

	isneg = 1;
	val = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		isneg = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		val = (10 * val) + *nptr - '0';
		nptr++;
	}
	return (val * isneg);
}