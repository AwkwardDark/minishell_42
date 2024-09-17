/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:38:09 by pierre            #+#    #+#             */
/*   Updated: 2024/09/17 12:19:53 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// && line[limiter_len] == '\n'))
// write(STDOUT_FILENO, "> ", 2);
// line = get_next_line(STDIN_FILENO);
// line = get_next_line(STDIN_FILENO);
static void	heredoc_work(char *limiter, int *pipe_fd, t_data *data)
{
	int		limiter_len;
	char	*line;
	char	*linenl;

	add_fdtogb(data->bin, pipe_fd[1]);
	here_docsignals(data);
	limiter_len = ft_strlen(limiter);
	close(pipe_fd[0]);
	line = readline("> ");
	while (line && !(ft_strncmp(limiter, line, limiter_len) == 0))
	{
		linenl = ft_strjoin(line, "\n");
		write(pipe_fd[1], linenl, ft_strlen(line) + 1);
		free(line);
		free(linenl);
		line = readline("> ");
	}
	sigint_exit(data);
	if (!line)
		ft_putstr_fd("ctrl + d\n", 2);
	else
		free(line);
	close(pipe_fd[1]);
	free_process(data);
	exit(EXIT_SUCCESS);
}

void	do_mydoc(char *limiter, t_data *data)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) < 0)
		error_disp_exit("pipex: pipe: ", strerror(errno), 1);
	signal(SIGQUIT, SIG_IGN);
	ret = fork();
	if (ret < 0)
		error_disp_exit("fork", strerror(errno), 1);
	if (ret == 0)
		heredoc_work(limiter, fd, data);
	simplecmd_wait(ret, data);
	signal(SIGQUIT, main_sigquit);
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
