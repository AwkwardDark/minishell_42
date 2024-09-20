/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 01:12:42 by pierre            #+#    #+#             */
/*   Updated: 2024/09/21 01:13:37 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_cmds_aux(char **cmd_arr, t_token *token, int i, int absolut)
{
	if (absolut && i == 0)
		cmd_arr[i] = (char *)malloc(sizeof(char)
				* (ft_strlen(&token->content[2]) + 1));
	else
		cmd_arr[i] = (char *)malloc(sizeof(char)
				* (ft_strlen(token->content) + 1));
	if (!cmd_arr[i])
		return ;
	cmd_arr[i][0] = 0;
	if (absolut && i == 0)
		ft_strcpy(cmd_arr[i], &token->content[2]);
	else
		ft_strcpy(cmd_arr[i], token->content);
}
