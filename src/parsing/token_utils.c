/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:36:24 by pajimene          #+#    #+#             */
/*   Updated: 2024/09/18 19:55:52 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*It sets the token_type of each node depending of the sybol with matchs*/
void	ft_token_symbol(char *content, t_token *token)
{
	if (content[0] == O_PAREN)
		token->token_type = O_PAR;
	if (content[0] == C_PAREN)
		token->token_type = C_PAR;
	if (content[0] == I_R && (ft_strlen(content) == 1))
		token->token_type = R_IN;
	if (content[0] == I_R && (ft_strlen(content) == 2))
		token->token_type = HEREDOC;
	if (content[0] == O_R && (ft_strlen(content) == 1))
		token->token_type = R_OUT;
	if (content[0] == O_R && (ft_strlen(content) == 2))
		token->token_type = APPEND;
	if (content[0] == P && (ft_strlen(content) == 1))
		token->token_type = PIPE;
	if (content[0] == P && (ft_strlen(content) == 2))
		token->token_type = OR;
	if (content[0] == '&')
		token->token_type = AND;
}
