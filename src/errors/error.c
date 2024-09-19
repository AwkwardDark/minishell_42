/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:59:36 by pierre            #+#    #+#             */
/*   Updated: 2024/09/19 23:23:09 by pierre           ###   ########.fr       */
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
	ft_memcpy(buffer, "minishell: ", 11);
	ft_memcpy(buffer + 11, cmd, cmd_len);
	ft_memcpy(buffer + 11 + cmd_len, ": ", 2);
	ft_memcpy(buffer + cmd_len + 11 + 2, error_message, error_len);
	ft_memcpy(buffer + cmd_len + error_len + 11 + 2, "\n", 1);
	buffer[cmd_len + error_len + 2 + 11 + 2] = 0;
	write(STDERR_FILENO, buffer, error_len + cmd_len + 1 + 11 + 2);
}

/* concatenate cmd and error_messsage and adds a \n 
(Without any Malloc) and exits */
void	error_disp_exit(char *error_message, char *cmd, int eno)
{
	char	buffer[500];
	int		cmd_len;
	int		error_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error_message);
	ft_memcpy(buffer, "minishell: ", 11);
	ft_memcpy(buffer + 11, cmd, cmd_len);
	ft_memcpy(buffer + cmd_len + 11, ": ", 2);
	ft_memcpy(buffer + cmd_len + 11 + 2, error_message, error_len);
	ft_memcpy(buffer + cmd_len + 11 + 2 + error_len, "\n", 1);
	buffer[cmd_len + 11 + 2 + error_len + 1] = 0;
	write(2, buffer, cmd_len + 11 + 2 + error_len + 1);
	if (eno >= 0)
		exit(eno);
}

void	cmdnotfound_exit(char **argv, t_data *data, t_token *token, int eno)
{
	char	buffer[500];
	int		len;

	len = ft_strlen(token->content);
	ft_memcpy(buffer, token->content, len);
	buffer[len] = 0;
	clr_gb(data->bin);
	clear_wordar(argv);
	ft_free_exit(data);
	error_disp_exit("command not found", buffer, eno);
}

void	permissiond_exit(char *path, t_data *data, char **argv, char *path2)
{
	char	buffer[500];

	if (path2)
		free(path2);
	if (argv)
		clear_wordar(argv);
	ft_memcpy(buffer, path, ft_strlen(path));
	buffer[ft_strlen(path)] = 0;
	clr_gb(data->bin);
	ft_free_exit(data);
	error_disp_exit("permission denied", buffer, 126);
}

/*It writes on the STDERR an error message*/
void	ft_error(int code)
{
	if (code == 0)
		ft_putstr2("minishell: quote syntax error\n", 2);
	if (code == 1)
		ft_putstr2("minishell: and (&&) logical operator syntax error\n", 2);
	if (code == 2)
		ft_putstr2("minishell: or (||) logical operator syntax error\n", 2);
	if (code == 3)
		ft_putstr2("minishell: heredoc (<<) syntax error\n", 2);
	if (code == 4)
		ft_putstr2("minishell: append (>>) syntax error\n", 2);
	if (code == 5)
		ft_putstr2("minishell: parenthesis syntax error\n", 2);
	if (code == 6)
		ft_putstr2("minishell: env list creation error\n", 2);
	if (code == 7)
		ft_putstr2("minishell: malloc error\n", 2);
}
