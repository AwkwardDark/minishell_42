/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:24:27 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:34:42 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	int				n;
	char			*res;
	unsigned char	v;

	v = c;
	res = NULL;
	str = (char *)s;
	n = 0;
	while (str[n])
	{
		if ((unsigned char)str[n] == v)
			res = &str[n];
		n++;
	}
	if ((unsigned char)str[n] == v)
		return (&str[n]);
	return (res);
}
