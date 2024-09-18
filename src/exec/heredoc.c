/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:38:09 by pierre            #+#    #+#             */
/*   Updated: 2024/09/18 23:42:44 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// && line[limiter_len] == '\n'))
// write(STDOUT_FILENO, "> ", 2);
// line = get_next_line(STDIN_FILENO);
// line = get_next_line(STDIN_FILENO);
static void	heredoc_work(char *limiter, int *pipe_fd, t_data *data, int is_last)
{
	int		limiter_len;
	char	*line;
	char	*linenl;

	limiter_len = ft_strlen(limiter);
	line = readline("> ");
	while (line && !(ft_strncmp(limiter, line, limiter_len) == 0))
	{
		linenl = ft_strjoin(line, "\n");
		if (is_last)
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
}

static void	do_mydocs_aux(t_token *token, t_data *data, int *pipe)
{
	char	*limiter;

	here_docsignals();
	close(pipe[0]);
	add_fdtogb(data->bin, pipe[1]);
	if (token->token_type == WORD)
		token = token->next;
	while (token != NULL && token->token_type == HEREDOC && g_signal == 0)
	{
		limiter = get_limiter(token);
		if (token->next != NULL && token->next->token_type == HEREDOC)
			heredoc_work(limiter, pipe, data, 0);
		else
			heredoc_work(limiter, pipe, data, 1);
		token = token->next;
	}
	free_process(data);
	exit(EXIT_SUCCESS);
}

void	do_mydoc(t_token *token, t_data *data)
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
		do_mydocs_aux(token, data, fd);
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
