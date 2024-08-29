/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:21:23 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:26:41 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_count_chars(long n)
{
	int	len;

	len = 0;
	len++;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while ((n / 10) != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	len = ft_count_chars((long)n);
	num = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, len + 1);
	len--;
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num / 10 != 0)
	{
		str[len] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	str[len] = num + '0';
	return (str);
}
