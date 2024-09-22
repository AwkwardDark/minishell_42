/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:34:32 by pierre            #+#    #+#             */
/*   Updated: 2024/09/22 20:09:23 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_routine(long long val, t_data *data)
{
	clr_gb(data->bin);
	ft_free_exit(data);
	printf("exit\n");
	if (val < 0)
		exit(val);
	exit(val);
}

// frees memory before exiting
static void	free_end(int exno, t_data *data, char *str)
{
	if (str)
		free(str);
	clr_gb(data->bin);
	ft_free_exit(data);
	exit(exno);
}

// check if the exit number is not overflow
static void	is_longlong(t_token *token, t_data *data)
{
	long long	val;
	int			ovrflw;
	char		*trim;
	int			len;

	ovrflw = 1;
	trim = ft_strtrim(token->content, " ");
	len = parse_exnum(trim);
	if (len == 0 || len < 0 || (*trim != '-' && len > 19)
		|| (*trim == '-' && len > 20))
	{
		ft_putstr2("minishell: exit: numeric argument required\n", 2);
		free_end(2, data, trim);
	}
	ft_check_overflow(trim, &len, &ovrflw);
	if (ovrflw != -1)
		val = ft_atoll(trim);
	free(trim);
	if (ovrflw == -1)
	{
		ft_putstr2("minishell: exit: numeric argument required\n", 2);
		free_end(2, data, NULL);
	}
	else
		exit_routine(val, data);
}

// handles exit builtin
void	ft_exit(t_token *token, t_data *data)
{
	if (token == NULL || token->token_type != WORD)
	{
		printf("exit\n");
		free_end(data->lst_exit_status, data, NULL);
	}
	if (token->next != NULL)
	{
		if (is_number(token->content) && get_errortype(token))
		{
			printf("exit\n");
			ft_putstr2("minishell: exit: too many arguments\n", 2);
			data->exit_status = 1;
			return ;
		}
		else
		{
			printf("exit\n");
			ft_putstr2("minishell: exit: numeric argument required\n", 2);
			free_end(2, data, NULL);
		}
	}
	is_longlong(token, data);
}
