/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pajimene <pajimene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:40:22 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/12 15:13:06 by pajimene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Pablo 
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"
# include "../libft/includes/libft.h"
# include <signal.h>

/*Color for the minishell prompt*/
# define GREEN "\033[0;92m"
# define RED "\033[0;91m"
# define GRAS "\033[1m"
# define RESET "\033[0m"

/*Message error macros, it's useful or it makes the code cleaner?*/

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

/*Testing utils*/
void	ft_print_expand_table(int *tab, int len);

// Pierre

// src/signals/handler.c
void	handler_slash(int code);
void	handler_c(int code);
void	handler_main(int code);
void	parenthandler(int code);
// void	child_sigs();red
void	handler_main(int code);
void	child_sigint(int code);
// void	child_heredoc(int code, siginfo_t *info, void *content);

/* /src/utils/free_exec.c */
void	free_exec(char *path, char **argv, char **env_arr);

/* src/utils/ls_env.c */
t_env	*ft_initenv(char *key, char *value);
void	ft_addlstenv(t_env **env, char *key, char *value);
void	ft_clrenv(t_env **head);
void	ft_clrenvnode(t_env *env);

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

/* src/builtins */
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(t_env *env);
void	ft_unset(char *var, t_data *data);
void	ft_export(t_env **env, char *key, char *value);
void	ft_echo(char **str, int NFLAG);

// src/exec/wait.c
void	wait_children(pid_t last_childm, t_data *data);
void	simplecmd_wait(int pid, t_data *data);

// src/exec/exec_operators.c
void	exec_or(t_btree *tree, t_data *data);
void	exec_and(t_btree *tree, t_data *data);

// single_exec
void	executer(t_data *data, t_token *token);
char	**lstenv_towordarr(t_env *env);
char	*get_paths(t_env *env);
char	*test_path(char *envpath, char *cmd);
char	*add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx);
char	**lstenv_towordarr(t_env *env);
char	**cmdlst_tocmdarr(t_token *token, int absolut);

// expand.c
void	ft_expand(t_token *lst, t_data *data);
char	*ft_find_exp_value(char *key, t_env *env);

// wildcard.c
void	ft_wildcard(t_token **lst, t_data *data);

// exec_utils.c
int		is_heredoc(t_token *token);
char 	*get_limiter(t_token *token);

//heredoc.c
void	do_mydoc(char *limiter, t_data *data);
//static void	heredoc_work(char *limiter, int *pipe_fd);

//src/exec/redirections.c
void	in_redirection(t_token *token);
void	out_redirection(t_token *token);
void	redirect_files(t_token *token, int *pipe, int flag, t_data *data);

// exec.c
void		exec_btree(t_btree *tree, t_data *data);
// static int		exec_pipes(t_btree *tree, t_env *env, int last_command)
// static int		parse_exec(t_token *token, t_env *env, int flag);

// src/errors/error.c
void	error_disp(char *cmd, char *error_message);
void	error_disp_exit(char *cmd, char *error_message, int eno);

#endif