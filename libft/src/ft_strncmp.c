/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:24:08 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:24:09 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*sp1;
	unsigned char	*sp2;

	sp1 = (unsigned char *) s1;
	sp2 = (unsigned char *) s2;
	i = 0;
	while (sp1[i] && sp2[i] && i < n)
	{
		if (sp1[i] != sp2[i])
			return (sp1[i] - sp2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (sp1[i] - sp2[i]);
}
