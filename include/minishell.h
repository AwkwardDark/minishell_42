/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:40:22 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/20 09:51:00 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "structs.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> //necessary?
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <limits.h>

/*Color for the minishell prompt*/
# define GREEN "\033[0;92m"
# define RED "\033[0;91m"
# define GRAS "\033[1m"
# define RESET "\033[0m"
# define PWD_ERROR "pwd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n"
# define CHDIR_PWD "Error: too many charachters in current working directory\n"

/*Message error macros, it's useful or it makes the code cleaner?*/
# define SIMPLE_COMMAND 2 

/*Character macros*/
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define SPACE ' '
# define TAB '\t'//we take in account the tabs for minishell?
# define O_PAREN '('
# define C_PAREN ')'
# define P '|'
# define I_R '<'
# define O_R '>'
# define DOLLAR '$'

extern int	g_signal;

/*Error and Memory managment*/
void	ft_free_exit(t_data *data);

/*Double Linked List utils*/
t_token	*ft_lstnew(char *content);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_insert_after(t_token *current, t_token *new);
void	ft_print_lst(t_token *lst);
void	ft_free_lst(t_token **lst);
void	ft_free_onetoken(t_token *token);

/*Redir*/
void	ft_redir_check(t_token **lst);

/*Parser, Lexer and Simple Syntax management*/
int		ft_init_data(char **envp, t_data *data);
void	ft_error(int code);
int		ft_parser(char *input, t_data *data);
void	ft_lexer(char *input, t_data *data);
void	ft_tokenize(t_token *lst);
int		ft_quote_syntax(char *input);
int		ft_operator_syntax(char *input, t_data *data);
int		ft_parenthesis_syntax(char *input, t_data *data);
int		ft_grammar_syntax(t_token *lst, t_data *data);
void	ft_remove_quotes(t_token *lst, t_data *data);
void	ft_pre_expand(t_token *lst);
void	ft_pre_wildcard(t_token *lst);

/*Parsing Utils*/
int		ft_str_is_quote(char *str);
int		ft_is_quote(char c, t_data *data);
int		ft_is_operator(char *input, int *i, t_data *data);
int		ft_is_symbol(char c);
int		ft_is_special(char c);
void	ft_token_symbol(char *content, t_token *token);
int		ft_count_exp(char *str);
int		ft_simple_wildcard(char *wildcard);
void	ft_print_lst(t_token *lst);

/*Testing utils*/
void	ft_print_expand_table(int *tab, int len);

// clr_gb.c
void	close_fds(t_gbcolector *bin);
void	clr_gb(t_gbcolector *bin);
void	free_process(t_data *data);

// gb_utils.c
void	add_fdtogb(t_gbcolector *gb, int fd);

// export_parse.c
int		keyparse(char *str);

// exit_utils.c
int		is_number(char *str);
int		get_errortype(t_token *token);
int		parse_exnum(char *cmd);
void	ft_check_overflow(char *trim, int *len, int *ovrflw);

// src/signals
// handler.c
void	child_sigint(int code);
void	here_docsignals(void);
void	heredoc_handler(int code);
void	sigint_exit(t_data *data);
// void	parent_sigquit(int code);
void	child_sigquit(int code);

// mainp_handler.c
void	parenthandler(int code);
void	main_sigint(int code);
void	main_sigquit(int code);

/* /src/utils/free_exec.c */
void	free_execve(char *path, char **argv, char **env_arr);
int		free_exec_pipe(t_data *data);
int		free_exec_fork(t_data *data);
int		free_exec_dup2(t_data *data);

/* src/utils/ls_env.c */
t_env	*ft_initenv(char *key, char *value);
void	ft_addlstenv(t_env **env, char *key, char *value);
void	ft_clrenv(t_env **head);
void	ft_clrenvnode(t_env *env);
char	*get_env(t_env *env, char *key);

/* src/utils/ft_cpyenv.c */
t_env	*ft_cpyenv(char **env);

/* src/tree/tree.c */
t_btree	*init_btree(t_token *token, t_btree *left, t_btree *right);
void	clr_btree(t_btree *tree);
t_token	*remove_parenthesis(t_token *token);
t_token	*get_startlst(t_token *token);
t_btree	*create_tokentree(t_token **token);

/* src/tree/tree_utils.c */
t_token	*ignore_parenthesis(t_token *token);
t_token	*contains_priority(t_token *token, int priority);
void	display_btree(t_btree *tree);
int		is_leaf(t_btree *tree);
void	display_type(t_type type);

// write_utils.c
int		ft_putstr2(char *str, int fd);

/* src/builtins */
void	ft_cd(t_token *token, t_data *data);
void	ft_pwd(t_token *token, t_data *data, int fd);
char	*get_cwd(void);
void	ft_env(t_data *data, int fd);
void	ft_unset(t_token *token, t_data *data);
void	ft_export(t_data *data, t_token *token, int fd);
void	add_or_replace(t_env **env, char *key, char *value);
void	ft_echo(t_token *token, int fd, t_data *data);
int		ft_is_builtins(char *cmd);
void	ft_exit(t_token *token, t_data *data);
void	exec_builtin(t_token *token, t_data *data);
void	exec_subbuiltin(t_token *token, t_data *data);
void	exec_btree_aux(t_btree *tree, t_data *data);

// src/exec/wait.c
void	wait_children(pid_t last_childm, t_data *data);
void	simplecmd_wait(int pid, t_data *data);

// src/exec/exec_operators.c
void	exec_or(t_btree *tree, t_data *data);
void	exec_and(t_btree *tree, t_data *data);

// exec/single_exec
void	executer(t_data *data, t_token *token);
char	**lstenv_towordarr(t_env *env);
char	*get_paths(t_env *env);
char	*test_path(char *envpath, char *cmd);

// utils/exec_utils.c
char	*add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx);
char	**lstenv_towordarr(t_env *env);
char	**cmdlst_tocmdarr(t_token *token, int absolut);

// exec/exec_utils.c
int		is_heredoc(t_token *token);
char	*get_limiter(t_token *token);

//src/exec/redirections.c
void	in_redirection(t_token *token, t_data *data);
void	out_redirection(t_token *token, t_data *data);

// expand.c
void	ft_expand(t_token *lst, t_data *data);
char	*ft_find_exp_value(char *key, t_data *data);
char	*ft_strjoin_expand(char *s1, char *s2);
char	*ft_extract_exp(char *str, int len);
char	*ft_create_new_expansion(char *str, int i, char *expanded, int new_len);

// wildcard.c
void	ft_wildcard(t_token **lst, t_btree *tree);

// exec_utils.c
int		is_heredoc(t_token *token);
char	*get_limiter(t_token *token);

//heredoc.c
void	do_mydoc(t_token *token, t_data *data);
char	*ft_heredoc_expansion(char *line, int i, t_data *data);
//static void	heredoc_work(char *limiter, int *pipe_fd);

//src/exec/redirections.c
void	redirect_files(t_token *token, int *pipe, int flag, t_data *data);

// exec.c
void	exec_btree(t_btree *tree, t_data *data);
// static int		exec_pipes(t_btree *tree, t_env *env, int last_command)
// static int		parse_exec(t_token *token, t_env *env, int flag);

// src/errors/error.c
void	error_disp(char *cmd, char *error_message);
void	error_disp_exit(char *cmd, char *error_message, int eno);
void	cmdnotfound_exit(char **argv, t_data *data, t_token *token, int eno);
void	permissiond_exit(char *path, t_data *data, char **argv, char *path2);

// src/errors/builtins_errors.c
void	errorcmd_failed(char *cmd, char *error);
void	errorcmd_failed2(char *cmd, char *arg, char *error);
void	nosuchfile_exit(char **argv, t_data *data, t_token *token, int eno);

#endif