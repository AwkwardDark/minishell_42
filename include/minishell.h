/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:40:22 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/04 23:54:14 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"

/* src/utils/ls_env.c */
t_env	*ft_initenv(char *key, char *value);
void	ft_addlstenv(t_env **env, char *key, char *value);
void	ft_clrenv(t_env **head);
void	ft_clrenvnode(t_env *env);

/* src/utils/ft_cpyenv.c */
t_env	*ft_cpyenv(char **env);

/* src/utils/token.c */
void	ft_free_lst(t_token **a);
t_token	*ft_lstnew(char *content, t_type type);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
void	ft_print_lst(t_token *lst);
void	display_type(t_type type);

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
int	is_leaf(t_btree *tree);

/* src/builtins */
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_env(t_env *env);
void	ft_unset(char *var, t_data *data);
void	ft_export(t_env **env, char *key, char *value);
void	ft_echo(char **str, int NFLAG);

// single_exec
void	executer(t_env *env, t_token *token);
char	**lstenv_towordarr(t_env *env);
char	*get_paths(t_env *env);
char	*test_path(char *envpath, char *cmd);
char	*add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx);
char	**lstenv_towordarr(t_env *env);
char	**cmdlst_tocmdarr(t_token *token);

// exec_utils.c
int		is_heredoc(t_token *token);
char 	*get_limiter(t_token *token);

//heredoc.c
void	do_mydoc(t_token *token, char *limiter);
// static void	heredoc_work(char *limiter, int *pipe_fd)

//src/exec/redirections.c
void	in_redirection(t_token *token);
void	out_redirection(t_token *token);
void	redirect_files(t_token *token, int *pipe, int flag, t_env *env);

// exec.c
int		exec_btree(t_btree *tree, t_env *env);
int		wait_children(pid_t last_child);
// static int		exec_pipes(t_btree *tree, t_env *env, int last_command)
// static int		parse_exec(t_token *token, t_env *env, int flag);

// src/errors/error.c
void	error_disp(char *cmd, char *error_message);
void	error_disp_exit(char *cmd, char *error_message, int eno);

#endif