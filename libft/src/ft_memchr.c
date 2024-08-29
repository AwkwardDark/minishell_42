/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:24:56 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:28:19 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	unsigned char	v;

	ptr_s = (unsigned char *)s;
	v = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr_s == v)
			return (ptr_s);
		ptr_s++;
		n--;
	}
	return (NULL);
}
