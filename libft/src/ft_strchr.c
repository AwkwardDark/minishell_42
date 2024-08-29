/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:23:05 by pierre            #+#    #+#             */
/*   Updated: 2024/08/01 00:10:45 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				n;
	unsigned char	v;
	char			*str;

	str = (char *)s;
	v = c;
	n = 0;
	if (s == 0)
		return (NULL);
	while (str[n])
	{
		if ((unsigned char)str[n] == v)
			return (&str[n]);
		n++;
	}
	if ((unsigned char)str[n] == v)
		return (&str[n]);
	return (NULL);
}
