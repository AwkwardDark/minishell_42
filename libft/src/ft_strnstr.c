/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:24:23 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:34:31 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	str = (char *)big;
	if (len == 0 && *little)
		return (NULL);
	if (len == 0 || !*little)
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		while (little[j] && little[j] == str[j + i] && j + i < len)
		{
			j++;
			if (little[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}
