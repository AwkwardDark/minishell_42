/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:01:14 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/11 11:06:32 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_expand_table(int *tab, int len)
{
	int	i;

	i = 0;
	if (!tab)
	{
		printf("NULL\n");
		return ;
	}
	while (i < len)
	{
		printf("%d\n", tab[i]);
		i++;
	}
}
