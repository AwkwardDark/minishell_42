/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:38:09 by pierre            #+#    #+#             */
/*   Updated: 2024/09/12 12:37:10 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	child read on STDIN until reading limiter its writes every time 
	on pipe[1] TODO a parsing in input to know if wwe need to expand 
	we should add a flag EXPAND to know it should be evaluatd in the do_mydoc
	Also check for Signals
*/
static void	heredoc_work(char *limiter, int *pipe_fd)
{
	int		limiter_len;
	char	*line;

	signal(SIGINT, child_sigint);
	limiter_len = ft_strlen(limiter);
	close(pipe_fd[0]);
	write(STDOUT_FILENO, "> ", 2);
	line = get_next_line(STDIN_FILENO);
	while (line && !(ft_strncmp(limiter, line, limiter_len) == 0
			&& line[limiter_len] == '\n'))
	{
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
	}
	if (!line)
		error_disp_exit("heredoc: ", "CTRL + d", 127);
	else
		free(line);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

void	do_mydoc(char *limiter, t_data *data)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) < 0)
		error_disp_exit("pipex: pipe: ", strerror(errno), 1);
	ret = fork();
	if (ret < 0)
		error_disp_exit("fork", strerror(errno), 1);
	if (ret == 0)
		heredoc_work(limiter, fd);
	simplecmd_wait(ret, data);
	if (g_signal == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			error_disp_exit("minishell", strerror(errno), 1);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
}
