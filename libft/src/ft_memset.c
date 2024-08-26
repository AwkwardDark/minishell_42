/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:24:57 by pierre            #+#    #+#             */
/*   Updated: 2024/04/08 15:40:07 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *set, int c, size_t n)
{
	unsigned char	v;
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)set;
	i = 0;
	v = (unsigned char) c;
	while (i < n)
	{
		ptr[i] = v;
		i++;
	}
	return (set);
}
