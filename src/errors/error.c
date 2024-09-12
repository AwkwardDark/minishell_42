/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:59:36 by pierre            #+#    #+#             */
/*   Updated: 2024/09/12 15:08:36 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* concatenate cmd and error_messsage and adds a \n (Without any Malloc) */
void	error_disp(char *cmd, char *error_message)
{
	char	buffer[500];
	int		cmd_len;
	int		error_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error_message);
	ft_memcpy(buffer, cmd, cmd_len);
	ft_memcpy(buffer + cmd_len, error_message, error_len);
	ft_memcpy(buffer + cmd_len + error_len, "\n", 1);
	buffer[cmd_len + error_len + 2] = 0;
	write(STDERR_FILENO, buffer, error_len + cmd_len + 1);
}

/* concatenate cmd and error_messsage and adds a \n 
(Without any Malloc) and exits */
void	error_disp_exit(char *cmd, char *error_message, int eno)
{
	char	buffer[500];
	int		cmd_len;
	int		error_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error_message);
	ft_memcpy(buffer, cmd, cmd_len);
	ft_memcpy(buffer + cmd_len, error_message, error_len);
	ft_memcpy(buffer + cmd_len + error_len, "\n", 1);
	buffer[cmd_len + error_len + 2] = 0;
	write(STDERR_FILENO, buffer, error_len + cmd_len + 1);
	exit(eno);
}

/*Before exiting the program, it free the environment list, the prompt input,
the token parsing list and the rest of malloc'd structs*/
void	ft_free_exit(t_data *data)
{
	if (data->env)
		ft_clrenv(&data->env);
	if (data->input)
		free(data->input);
	// if (data->token_lst)
	// 	ft_free_lst(&data->token_lst);
	if (data)
	{
		if (data->bin)
			free(data->bin);
		free(data);
	}
	rl_clear_history();
}

/*It writes on the STDERR an error message*/
void	ft_error(int code)
{
	if (code == 0)
		ft_putstr_fd("minishell: quote syntax error\n", 2);
	if (code == 1)
		ft_putstr_fd("minishell: and (&&) logical operator syntax error\n", 2);
	if (code == 2)
		ft_putstr_fd("minishell: or (||) logical operator syntax error\n", 2);
	if (code == 3)
		ft_putstr_fd("minishell: heredoc (<<) syntax error\n", 2);
	if (code == 4)
		ft_putstr_fd("minishell: append (>>) syntax error\n", 2);
	if (code == 5)
		ft_putstr_fd("minishell: parenthesis syntax error\n", 2);
	if (code == 6)
		ft_putstr_fd("minishell: env list creation eroor\n", 2);
	if (code == 7)
		ft_putstr_fd("minishell: malloc error\n", 2);
}
