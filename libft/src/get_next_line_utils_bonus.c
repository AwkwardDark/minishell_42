/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:58:51 by pierre            #+#    #+#             */
/*   Updated: 2024/07/31 23:55:02 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoinaux(char *buffer, char *str)
{
	char	*join;

	join = malloc(sizeof(char) * (ft_strlen(buffer) + ft_strlen(str) + 1));
	if (!join)
		return (NULL);
	join[0] = '\0';
	ft_strcat(join, buffer);
	ft_strcat(join, str);
	free(buffer);
	return (join);
}

/* static char	*ft_strcat(char *dest, const char *src)
{
	if (!src)
		return (dest);
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (dest);
} */

/* char	*ft_strchr(const char *s, int c)
{
	int				n;
	unsigned char	v;
	char			*str;

	str = (char *)s;
	v = c;
	n = 0;
	if (s == 0)
		return (NULL);
	while (str[n])
	{
		if ((unsigned char)str[n] == v)
			return (&str[n]);
		n++;
	}
	if ((unsigned char)str[n] == v)
		return (&str[n]);
	return (NULL);
} */

/* int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while (str[i])
		i++;
	return (i);
} */
