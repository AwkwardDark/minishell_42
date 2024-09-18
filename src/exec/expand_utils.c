/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:14:35 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/18 20:19:31 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_join_str(char *join, char *s1, char *s2)
{
	int	i;

	i = 0;
	while (*s1)
	{
		join[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		join[i] = *s2;
		i++;
		s2++;
	}
	join[i] = '\0';
	return (join);
}

/*Adapted version of ft_strjoin for expand edge cases*/
char	*ft_strjoin_expand(char *s1, char *s2)
{
	char	*join;

	if (!s1 && !s2)
	{
		join = ft_calloc(sizeof(char), 1);
		return (join);
	}
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	return (ft_join_str(join, s1, s2));
}
