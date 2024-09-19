/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:34:33 by pierre            #+#    #+#             */
/*   Updated: 2024/09/18 23:53:45 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

// return 1 all are numbers then error and exit 2
// return 0 not all are number then error and exit
// status 2 but no exit form minishell
int	get_errortype(t_token *token)
{
	char	*str;

	while (token != NULL && token->token_type == WORD)
	{
		str = ft_strtrim(token->content, " ");
		if (is_number(str))
		{
			free(str);
			return (1);
		}
		free(str);
		token = token->next;
	}
	return (0);
}

int	parse_exnum(char *cmd)
{
	int	len;

	len = 0;
	if (!cmd)
		return (-1);
	if (*cmd == '-')
	{
		cmd++;
		len++;
	}
	while (ft_isdigit(*cmd) && *cmd == '0')
		cmd++;
	while (ft_isdigit(*cmd))
	{
		len++;
		cmd++;
	}
	while (*cmd == ' ')
		cmd++;
	if (*cmd != '\0')
		return (-1);
	return (len);
}

void	ft_check_overflow(char *trim, int *len, int *ovrflw)
{
	char	*llong_min;
	char	*llong_max;
	int		sign;

	llong_min = "-9223372036854775808";
	llong_max = "9223372036854775807";
	sign = 1;
	if (trim[0] == '-')
		sign = -1;
	if (*len == 19 && (sign == 1) && ft_strcmp(trim, llong_max) > 0)
		*ovrflw = -1;
	if (*len == 20 && ft_strcmp(trim, llong_min) > 0)
		*ovrflw = -1;
}
