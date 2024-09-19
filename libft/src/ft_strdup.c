/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:23:25 by pierre            #+#    #+#             */
/*   Updated: 2024/09/19 13:56:36 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*ptr;
	int		n;

	if (!s)
	{
		ptr = ft_calloc(1, sizeof(char));
		return (ptr);
	}
	len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	n = 0;
	while (s[n])
	{
		ptr[n] = s[n];
		n++;
	}
	ptr[n] = '\0';
	return (ptr);
}
