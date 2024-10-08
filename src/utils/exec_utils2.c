/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 01:12:42 by pierre            #+#    #+#             */
/*   Updated: 2024/09/23 01:30:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_cmds_aux(char **cmd_arr, t_token *token, int i)
{
	cmd_arr[i] = (char *)malloc(sizeof(char)
			* (ft_strlen(token->content) + 1));
	if (!cmd_arr[i])
		return ;
	cmd_arr[i][0] = 0;
	ft_strcpy(cmd_arr[i], token->content);
}
