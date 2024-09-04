/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:36:24 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/04 13:17:40 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_symbol(char *content, t_token *token)
{
	if (content[0] == O_PAREN)
		token->token_type = O_PAR;
	if (content[0] == C_PAREN)
		token->token_type = C_PAR;
	if (content[0] == I_R && (ft_strlen(content) == 1))
		token->token_type = IN_R;
	if (content[0] == I_R && (ft_strlen(content) == 2))
		token->token_type = HEREDOC;
	if (content[0] == O_R && (ft_strlen(content) == 1))
		token->token_type = OUT_R;
	if (content[0] == O_R && (ft_strlen(content) == 2))
		token->token_type = APPEND;
	if (content[0] == P && (ft_strlen(content) == 1))
		token->token_type = PIPE;
	if (content[0] == P && (ft_strlen(content) == 2))
		token->token_type = OR;
	if (content[0] == '&')
		token->token_type = AND;
}
