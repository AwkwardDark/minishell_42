/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:22:21 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/17 12:28:44 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_symbol(char c)
{
	char	*set;
	int		i;

	i = 0;
	set = "()><|&";
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_str_is_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_special(char c)
{
	char	*special;
	int		i;

	i = 0;
	special = "!@#$%^&*()-+=[]{}|\\;:'\"<>,.?/~` ";

	while (special[i])
	{
		if (c == special[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_simple_wildcard(char *wildcard)
{
	int	i;

	i = 0;
	while (wildcard[i])
	{
		if (wildcard[i] != '*')
			return (0);
		i++;
	}
	return (1);
}
