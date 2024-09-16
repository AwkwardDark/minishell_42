/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_gb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:42:53 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/16 17:55:51 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clr_gb(t_gbcolector *bin)
{
	int i;

	i = 0;
	while (i < 1000 && bin->fds[i] != -1)
	{
		close(bin->fds[i]);
		i++;
	}
	// fprintf(stderr, "beginning to free\n");
	//printf("here\n");
	//printf("\n\nAfter left -> %s\n\n", bin->tree->left_child->token->content);
	//printf("\n\nAfter right -> %s\n\n", bin->tree->right_child->token->content);
	clr_btree(bin->tree);
}

void	free_process(t_data *data)
{
	clr_gb(data->bin);
	ft_free_exit(data);
}
