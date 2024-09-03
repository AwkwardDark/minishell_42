/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:40:22 by pbeyloun          #+#    #+#             */
/*   Updated: 2024/09/03 14:28:42 by pierre           ###   ########.fr       */
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

/* pipex and bonus */
int		pipex(char **cmds, t_pipe data, int argc);
int		pipex_bonus(char **cmds, t_pipe data, int argc);
int		redirect_io(t_pipe data, char *cmd, int flag);
void	redirect_files(char *cmd, t_pipe data, int *pipe, int flag);
void	executer(t_pipe data, char *cmd);
char	*get_paths(t_env *env);
char	*test_path(char *envpath, char *cmd);
void	clear_wordar(char **str);
char	*add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx);
t_pipe	init_data(char **argv, int argc, char **envp);
void	error_disp(char *cmd, char *error_message);
void	error_disp_exit(char *cmd, char *mdl, char *error_message, int eno);
int		wait_children(pid_t last_child);

// single_exec
char	**lstenv_towordarr(t_env *env);

#endif