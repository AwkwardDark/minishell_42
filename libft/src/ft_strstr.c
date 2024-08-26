/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:24:31 by pierre            #+#    #+#             */
/*   Updated: 2024/05/02 14:53:16 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = (char *)haystack;
	while (str[i])
	{
		j = 0;
		while (needle[j] && needle[j] == str[j + i])
		{
			j++;
			if (needle[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
