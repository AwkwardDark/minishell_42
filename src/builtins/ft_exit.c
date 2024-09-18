/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:34:32 by pierre            #+#    #+#             */
/*   Updated: 2024/09/18 00:41:45 by pierre           ###   ########.fr       */
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

 static void	free_end(int exno, t_data *data, char *str)
{
	if (str)
		free(str);
	clr_gb(data->bin);
	ft_free_exit(data);
	exit(exno);
}

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
// return 0 not all are number then error and exit status 2 but no exit form minishell
static int	get_errortype(t_token *token)
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

static int	parse_exnum(char *cmd)
{
	int	len;

	len = 0;
	if (!cmd)
		return (-1);
	if (*cmd == '-')
		cmd++;
	while (ft_isdigit(*cmd))
	{
		if (*cmd != '0')
			len++;
		cmd++;
	}
	while (*cmd == ' ')
		cmd++;
	if (*cmd != '\0')
		return (-1);
	return (len);
}

static void	is_longlong(t_token *token, t_data *data)
{
	long long	val;
	char		*trim;
	int			len;

	trim = ft_strtrim(token->content, "");
	len = parse_exnum(trim);
	if (len == 0 || len < 0 || (*trim != '-' && len > 19) || (*trim == '-' && len > 20))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		free_end(2, data, trim);
	}
	val = ft_atoll(trim);
	free(trim);
	if ((!ft_strcmp(trim, "9223372036854775807") && val != 9223372036854775807)
		|| (!ft_strcmp(trim, "-9223372036854775806") && val != -9223372036854775806))
	{
		fprintf(stderr, "skks\n");
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		free_end(2, data, NULL);
	}
	else
		exit_routine(val, data);
}

void	ft_exit(t_token *token, t_data *data)
{

	if (token == NULL || token->token_type != WORD)
		free_end(0, data, NULL);
	if (token->next != NULL )
	{
		if (get_errortype(token))
		{
			printf("exit\n");
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			data->exit_status = 127;
			return ;
		}
		else
		{
			printf("exit\n");
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			free_end(2, data, NULL);
		}
	}
	is_longlong(token, data);

}
