/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:24:39 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:35:21 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*str;
	unsigned int		n;
	unsigned int		size;

	n = 0;
	str = NULL;
	size = 0;
	if (start < ft_strlen(s))
	{
		while (s[start + n] && n < len)
			n++;
	}
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	size = n;
	n = 0;
	while (n < size)
	{
		str[n] = s[n + start];
		n++;
	}
	str[n] = '\0';
	return (str);
}
