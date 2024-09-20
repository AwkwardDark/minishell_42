/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:14:35 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/20 12:15:21 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// Finds for the expansion value of an enviroment variable
char	*ft_find_exp_value(char *key, t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (!ft_strcmp(key, "?"))
		{
			data->free_flag = 1;
			if (g_signal == 0)
				return (ft_itoa(data->lst_exit_status));
			else
				return (ft_itoa(g_signal + 128));
		}
		if (!ft_strcmp(key, current->key))
		{
			data->free_flag = 0;
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

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
	if (!s1 || !s1[0])
		return (ft_strdup(s2));
	if (!s2 || !s2[0])
		return (ft_strdup(s1));
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
		return (NULL);
	return (ft_join_str(join, s1, s2));
}
