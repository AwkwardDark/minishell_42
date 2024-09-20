/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:42:44 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/20 11:43:40 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errorcmd_failed(char *cmd, char *error)
{
	char	buffer[500];
	int		error_len;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error);
	ft_memcpy(buffer, "minishell: ", 11);
	ft_memcpy(buffer + 11, cmd, cmd_len);
	ft_memcpy(buffer + 11 + cmd_len, ": ", 2);
	ft_memcpy(buffer + 11 + cmd_len + 2, error, error_len);
	buffer[11 + cmd_len + 2 + error_len] = 0;
	ft_putstr2(buffer, 2);
}

void	errorcmd_failed2(char *cmd, char *arg, char *error)
{
	char	buffer[500];
	int		arg_len;
	int		error_len;
	int		cmd_len;

	arg_len = ft_strlen(arg);
	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error);
	ft_memcpy(buffer, "minishell: ", 11);
	ft_memcpy(buffer + 11, cmd, cmd_len);
	ft_memcpy(buffer + 11 + cmd_len, ": ", 2);
	ft_memcpy(buffer + 11 + cmd_len + 2, arg, arg_len);
	ft_memcpy(buffer + 11 + cmd_len + 2 + arg_len, ": ", 2);
	ft_memcpy(buffer + 11 + cmd_len + 4 + arg_len, error, error_len);
	ft_memcpy(buffer + 11 + cmd_len + 4 + arg_len + error_len, "\n", 1);
	buffer[11 + cmd_len + 4 + error_len + arg_len + 1] = 0;
	ft_putstr2(buffer, 2);
}

/*Before exiting the program, it frees the environment list, the prompt input,
and data and bin structures. Also it clears the prompt history*/
void	ft_free_exit(t_data *data)
{
	if (data->env)
		ft_clrenv(&data->env);
	if (data->export)
		ft_clrenv(&data->export);
	if (data->input)
		free(data->input);
	if (data)
	{
		if (data->bin)
			free(data->bin);
		free(data);
	}
	rl_clear_history();
}

// shoudl be in the file errors.c but too many functions
void	nosuchfile_exit(char **argv, t_data *data, t_token *token, int eno)
{
	char	buffer[500];
	int		len;

	len = ft_strlen(token->content);
	ft_memcpy(buffer, token->content, len);
	buffer[len] = 0;
	clr_gb(data->bin);
	clear_wordar(argv);
	ft_free_exit(data);
	error_disp_exit("no such file or directory", buffer, eno);
}

// shoudl be in the file errors.c but too many functions
void	isdirectory_exit(char **argv, t_data *data, t_token *token, int eno)
{
	char	buffer[500];
	int		len;

	len = ft_strlen(token->content);
	ft_memcpy(buffer, token->content, len);
	buffer[len] = 0;
	clr_gb(data->bin);
	clear_wordar(argv);
	ft_free_exit(data);
	error_disp_exit("is a directory", buffer, eno);
}