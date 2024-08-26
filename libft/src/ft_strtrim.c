/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 00:24:36 by pierre            #+#    #+#             */
/*   Updated: 2024/04/15 00:35:13 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_is_set(char c, char const *set)
{
	int	n;

	n = 0;
	while (set[n])
	{
		if (c == set[n])
			return (1);
		n++;
	}
	return (0);
}

static int	ft_count_start(char const *s1, char const *set)
{
	int	count;

	count = 0;
	while (*s1)
	{
		if (ft_is_set(*s1, set))
			count++;
		else
			break ;
		s1++;
	}
	return (count);
}

static int	ft_count_end(char const *s1, char const *set, int len)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (ft_is_set(*s1, set))
			count++;
		else
			break ;
		i++;
		s1--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*str;
	int		len_after;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (len == ft_count_end(&s1[len - 1], set, len))
		len_after = 0;
	else
		len_after = len - (ft_count_end(&s1[len - 1], set, len)
				+ ft_count_start(s1, set));
	str = (char *)malloc(sizeof(char) * (len_after + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	if (len_after == 0)
		return (str);
	ft_strncpy(str, &s1[ft_count_start(s1, set)], len_after);
	return (str);
}
