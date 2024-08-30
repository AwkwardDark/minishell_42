/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:47:04 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/08/30 15:00:12 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **str, int NFLAG)
{
	if (!str && !NFLAG)
		printf("\n");
	else if (!str && NFLAG)
		return ;
	else
	{
		while (*str)
		{
			printf("%s", *str);
			if (*(str + 1) != NULL)
				printf(" ");
			str++;
		}
	}
	if (!NFLAG)
		printf("\n");
}
