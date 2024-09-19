/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:06:51 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/20 00:17:02 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// frees only one node 
void	ft_free_onetoken(t_token *token)
{
	if (!token)
		return ;
	free(token->content);
	free(token);
}
