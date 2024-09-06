/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:48:43 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/06 17:21:52 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_quotex(char c, char *data)
{
	if (c == S_QUOTE)
	{
		*data = S_QUOTE;
		return (1);
	}
	if (c == D_QUOTE)
	{
		*data = D_QUOTE;
		return (1);
	}
	return (0);
}

void	ft_print_quotes(char *str)
{
	char 	*new;
	int 	i;
	int 	j;
	int 	flag;
	char	data = '\0';
	
	printf("old len -> %zu\n", ft_strlen(str));
	printf("old len quote-> %d\n", ft_count_quotes(str));
	new = ft_calloc(sizeof(char), (ft_strlen(str) - ft_count_quotes(str) + 1));
	i = 0;
	j = 0;
	flag = 1;
	while (str[i])
	{
		if (str[i] == data)
		{
			i++;
			flag = 1;
			data = '\0';
		}
		if (flag)
		{
			if (ft_is_quotex(str[i], &data))
			{
				i++;
				flag = 0;
			}
		}
		if (str[i] && str[i] != data)
		{
			new[j] = str[i];
			i++;
			j++;
		}
	}
	printf("new string len -> %zu\n", ft_strlen(new));
	printf(GRAS "new string -> %s\n\n" RESET, new);
}

int main(int ac, char **av)
{
	if (ac == 2)
		ft_print_quotes(av[1]);
	return (0);
}