/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:22:12 by pierre            #+#    #+#             */
/*   Updated: 2024/05/02 14:51:30 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dest;
	unsigned int		i;
	unsigned char		uc;

	ptr_src = (const unsigned char *)src;
	ptr_dest = (unsigned char *)dest;
	uc = (unsigned char)c;
	i = 0;
	while (ptr_src[i] != uc && i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	if (ptr_src[i] != c)
		return (NULL);
	ptr_dest[i] = ptr_src[i];
	return ((void *)&ptr_dest[i]);
}
