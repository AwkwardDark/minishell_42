/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:23:58 by pierre            #+#    #+#             */
/*   Updated: 2024/05/02 14:52:54 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		len;

	len = ft_strlen(s);
	str = ft_strnew(len);
	while (*s)
	{
		*str = (*f)(*s);
		s++;
		str++;
	}
	return (str);
}
