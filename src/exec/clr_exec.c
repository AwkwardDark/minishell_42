/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:43:30 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/13 12:08:05 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*clr_execnopath(char **argv, t_data *data, t_token *token)
{
	char	*word;
	char	*temp;

	word = NULL;
	while (token->token_type == WORD && token != NULL)
	{
		temp = ft_strdup(token->content);
		word = ft_strjoin(word, token->content);
		token = token->next;
		free(temp);
	}
	clr_gb(data->bin);
	clear_wordar(argv);
	ft_free_exit(data);
	return (word)
} */